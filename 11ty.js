// .eleventy.js
module.exports = function(eleventyConfig) {
    // Copy your static assets to the output folder
    eleventyConfig.addPassthroughCopy("src/assets");
    eleventyConfig.addPassthroughCopy("css");
    eleventyConfig.addPassthroughCopy("images");

    // Create categories collection for navigation
    eleventyConfig.addCollection("categories", function(collection) {
        let categories = new Set();
        collection.getAll().forEach(item => {
            if (item.data.category) {
                categories.add(item.data.category);
            }
        });
        return Array.from(categories).sort();
    });

    // Create navigation data structure
    eleventyConfig.addCollection("navData", function(collection) {
        const allItems = collection.getAll();
        
        // Get unique types for filtering
        const types = new Set();
        const genres = new Set();
        
        allItems.forEach(item => {
            if (item.data.type) types.add(item.data.type);
            if (item.data.genres) {
                // Assuming genres is an array
                const itemGenres = Array.isArray(item.data.genres) 
                    ? item.data.genres 
                    : [item.data.genres];
                itemGenres.forEach(genre => {
                    if (genre) genres.add(genre.trim());
                });
            }
        });
        
        return {
            types: Array.from(types).sort(),
            genres: Array.from(genres).sort(),
            totalItems: allItems.length
        };
    });

    // FILTER: Sort by Newest (Year) then Popularity
    eleventyConfig.addFilter("sortLatest", (posts) => {
        if (!posts) return [];
        return [...posts].sort((a, b) => {
            const yearA = parseInt(a.year) || 0;
            const yearB = parseInt(b.year) || 0;
            const popA = parseInt(a.popularity) || 0;
            const popB = parseInt(b.popularity) || 0;
            
            return yearB - yearA || popB - popA;
        });
    });

    // FILTER: Filter by Type (movie, anime, tv, series)
    eleventyConfig.addFilter("filterByType", (posts, type) => {
        if (!posts) return [];
        return posts.filter(post => post.type === type);
    });

    // FILTER: Filter by Genre
    eleventyConfig.addFilter("filterByGenre", (posts, genre) => {
        if (!posts) return [];
        return posts.filter(post => {
            if (!post.genres) return false;
            const postGenres = Array.isArray(post.genres) ? post.genres : [post.genres];
            return postGenres.some(g => g && g.trim().toLowerCase() === genre.toLowerCase());
        });
    });

    // FILTER: Top Airing Logic
    eleventyConfig.addFilter("getTopAiring", (posts) => {
        if (!posts) return [];
        return posts
            .filter(post => post.status === "ongoing" || post.status === "airing")
            .sort((a, b) => {
                const popA = parseInt(a.popularity) || 0;
                const popB = parseInt(b.popularity) || 0;
                return popB - popA;
            });
    });

    // FILTER: Hero Selection (Featured or High Rating/Popularity)
    eleventyConfig.addFilter("getHero", (posts) => {
        if (!posts) return [];
        return posts
            .filter(post => post.featured === true || (post.rating && post.rating >= 8.5))
            .sort((a, b) => {
                const yearA = parseInt(a.year) || 0;
                const yearB = parseInt(b.year) || 0;
                return yearB - yearA;
            })
            .slice(0, 10);
    });

    // FILTER: Recommended (High rating + popularity)
    eleventyConfig.addFilter("getRecommended", (posts) => {
        if (!posts) return [];
        return posts
            .filter(post => post.rating && post.rating >= 8.0)
            .sort((a, b) => {
                const ratingA = parseFloat(a.rating) || 0;
                const ratingB = parseFloat(b.rating) || 0;
                const popA = parseInt(a.popularity) || 0;
                const popB = parseInt(b.popularity) || 0;
                return (ratingB - ratingA) || (popB - popA);
            });
    });

    // FILTER: Get season data for a show
    eleventyConfig.addFilter("getSeasonData", (posts, showTitle, seasonNumber) => {
        if (!posts) return {};
        
        // Try to find exact season data
        const exactMatch = posts.find(post => {
            const postTitle = post.title.toLowerCase();
            const searchTitle = showTitle.toLowerCase();
            const hasSeason = post.seasonNumber === seasonNumber;
            
            return postTitle.includes(searchTitle) && hasSeason;
        });
        
        if (exactMatch) {
            return {
                title: exactMatch.title,
                year: exactMatch.year,
                episodes: exactMatch.episodes,
                rating: exactMatch.rating,
                slug: exactMatch.slug || exactMatch.title.toLowerCase().replace(/[^a-z0-9]/g, '-')
            };
        }
        
        // Fallback: Create season data
        return {
            title: `${showTitle.charAt(0).toUpperCase() + showTitle.slice(1)} - Season ${seasonNumber}`,
            year: "N/A",
            episodes: "N/A",
            rating: "N/A",
            slug: `${showTitle.toLowerCase().replace(/[^a-z0-9]/g, '-')}-season-${seasonNumber}`
        };
    });

    // FILTER: Get season slug
    eleventyConfig.addFilter("getSeasonSlug", (posts, showTitle, seasonNumber) => {
        if (!posts) return '';
        
        const seasonPost = posts.find(post => {
            const postTitle = post.title.toLowerCase();
            const searchTitle = showTitle.toLowerCase();
            return postTitle.includes(searchTitle) && post.seasonNumber === seasonNumber;
        });
        
        if (seasonPost) {
            return seasonPost.slug || seasonPost.title.toLowerCase().replace(/[^a-z0-9]/g, '-');
        }
        
        return `${showTitle.toLowerCase().replace(/[^a-z0-9]/g, '-')}-season-${seasonNumber}`;
    });

    // FILTER: Range for creating season numbers
    eleventyConfig.addFilter("range", (start, end) => {
        const result = [];
        for (let i = start; i <= end; i++) {
            result.push(i);
        }
        return result;
    });

    // FILTER: Get saved status from localStorage (for 11ty)
    eleventyConfig.addFilter("getSavedStatus", (itemId) => {
        // This runs at build time, returns default
        return { status: 'none', icon: 'favorite' };
    });

    // FILTER: Truncate text
    eleventyConfig.addFilter("truncate", (str, num) => {
        if (!str) return "";
        if (str.length <= num) return str;
        return str.slice(0, num) + "...";
    });

    // FILTER: Capitalize first letter
    eleventyConfig.addFilter("capitalize", (str) => {
        if (!str) return "";
        return str.charAt(0).toUpperCase() + str.slice(1);
    });

    // FILTER: Slugify for URLs
    eleventyConfig.addFilter("slugify", (str) => {
        if (!str) return "";
        return str.toLowerCase()
            .replace(/[^a-z0-9\s-]/g, '') // Remove special chars
            .replace(/\s+/g, '-')         // Replace spaces with hyphens
            .replace(/-+/g, '-')          // Replace multiple hyphens with single
            .trim();
    });

    // FILTER: Format number with commas
    eleventyConfig.addFilter("formatNumber", (num) => {
        if (!num) return "0";
        return num.toString().replace(/\B(?=(\d{3})+(?!\d))/g, ",");
    });

    // Add dump filter for debugging
    eleventyConfig.addFilter("dump", obj => JSON.stringify(obj, null, 2));

    // Shortcode for current year in footer
    eleventyConfig.addShortcode("currentYear", () => {
        return new Date().getFullYear();
    });

    // Shortcode for search form
    eleventyConfig.addShortcode("searchForm", (placeholder = "What are you looking for?") => {
        return `
        <form action="/search/" method="get" class="search-form" role="search">
            <input type="text" name="q" placeholder="${placeholder}" aria-label="Search">
            <button type="submit" aria-label="Submit search">
                <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                    <circle cx="11" cy="11" r="8"/>
                    <path d="m21 21-4.35-4.35"/>
                </svg>
            </button>
        </form>
        `;
    });

    // Add a global data file for site-wide navigation
    eleventyConfig.addGlobalData("site", {
        title: "Media Library",
        description: "Your personal media collection",
        url: "https://example.com",
        nav: [
            { name: "Home", url: "/" },
            { name: "Movies", url: "/movies/" },
            { name: "TV Shows", url: "/tv/" },
            { name: "Anime", url: "/anime/" },
            { name: "Browse", url: "/browse/" }
        ]
    });

    return {
        dir: {
            input: "src",
            output: "_site",
            data: "_data",
            includes: "_includes",
            layouts: "_layouts"
        },
        templateFormats: ["html", "njk", "md", "11ty.js"],
        markdownTemplateEngine: "njk",
        htmlTemplateEngine: "njk",
        dataTemplateEngine: "njk"
    };
};
