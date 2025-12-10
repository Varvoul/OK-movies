/**
 * Global Search Component for Quravel Streaming Platform
 * Compact popup search with filters and scrollable results
 */

class GlobalSearch {
    constructor(options = {}) {
        // Configuration options
        this.config = {
            dataUrl: options.dataUrl || 'data/posts.json',
            searchIcon: options.searchIcon || 'searchIcon',
            searchBox: options.searchBox || 'searchBox',
            searchInput: options.searchInput || 'searchInput',
            filterBtn: options.filterBtn || 'filterBtn',
            filterDropdown: options.filterDropdown || 'filterDropdown',
            resultsContainer: options.resultsContainer || 'resultsContainer',
            resultsList: options.resultsList || 'resultsList',
            viewAllBtn: options.viewAllBtn || 'viewAllBtn',
            maxResults: options.maxResults || 10,
            maxViewAllResults: options.maxViewAllResults || 50,
            debounceDelay: options.debounceDelay || 300,
            placeholderImage: options.placeholderImage || 'https://via.placeholder.com/60x90/2d3748/fff?text=No+Image',
            ...options
        };

        // Component state
        this.allPosts = [];
        this.isLoaded = false;
        this.searchCache = new Map();
        this.currentSearch = '';
        this.selectedGenres = new Set();
        this.selectedContentType = 'all';
        this.sortBy = 'relevance';
        this.debounceTimer = null;
        this.isSearchOpen = false;

        // Initialize the component
        this.init();
    }

    /**
     * Initialize the global search component
     */
    async init() {
        await this.loadContent();
        this.setupUI();
        this.setupEventListeners();
        this.injectStyles();
        console.log('🔍 Compact Global Search initialized');
    }

    /**
     * Load all content from the data source
     */
    async loadContent() {
        try {
            const response = await fetch(this.config.dataUrl);
            const data = await response.json();
            this.allPosts = data.posts || [];
            this.isLoaded = true;
            console.log(`✅ Loaded ${this.allPosts.length} posts for search`);
            
            // Build search index for faster lookups
            this.buildSearchIndex();
            
        } catch (error) {
            console.error('❌ Error loading search content:', error);
            this.handleLoadError(error);
        }
    }

    /**
     * Build search index for faster lookups
     */
    buildSearchIndex() {
        this.searchIndex = this.allPosts.map((post, index) => ({
            ...post,
            searchableTitles: this.getSearchableTitles(post),
            normalizedYear: post.year ? post.year.toString() : '',
            genres: post.genres || [],
            contentType: post.type || 'Unknown'
        }));
    }

    /**
     * Get all searchable titles for a post
     */
    getSearchableTitles(post) {
        const titles = [];
        if (post.title) titles.push(post.title.toLowerCase());
        if (post.title_en) titles.push(post.title_en.toLowerCase());
        if (post.title_jp) titles.push(post.title_jp.toLowerCase());
        if (post.alternative_titles && Array.isArray(post.alternative_titles)) {
            post.alternative_titles.forEach(title => {
                if (title) titles.push(title.toLowerCase());
            });
        }
        return titles;
    }

    /**
     * Set up the UI components
     */
    setupUI() {
        // Create search box if not exists
        const existingSearchBox = document.getElementById(this.config.searchBox);
        if (!existingSearchBox) {
            this.createSearchBox();
        }

        // Initialize filter dropdown content
        this.initializeFilterDropdown();
    }

    /**
     * Create the search box element
     */
    createSearchBox() {
        const searchBox = document.createElement('div');
        searchBox.id = this.config.searchBox;
        searchBox.className = 'compact-search-box';
        searchBox.style.cssText = `
            display: none;
            position: absolute;
            top: 100%;
            right: 0;
            width: 450px;
            background: #1a283b;
            border-radius: 12px;
            box-shadow: 0 10px 25px rgba(0, 0, 0, 0.5);
            z-index: 1000;
            overflow: hidden;
            border: 1px solid #2d3748;
        `;

        searchBox.innerHTML = `
            <div class="search-header">
                <div class="search-input-wrapper">
                    <input 
                        type="text" 
                        id="${this.config.searchInput}"
                        class="search-input"
                        placeholder="Search movies, shows, anime..."
                        autocomplete="off"
                    >
                    <div class="search-actions">
                        <button id="${this.config.filterBtn}" class="filter-btn">
                            <svg width="16" height="16" viewBox="0 0 16 16" fill="none">
                                <path d="M14 2H2L6.5 8.5V13L9.5 14.5V8.5L14 2Z" stroke="currentColor" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
                            </svg>
                            Filter
                        </button>
                    </div>
                </div>
                <div id="${this.config.filterDropdown}" class="filter-dropdown">
                    <div class="filter-section">
                        <h4>Content Type</h4>
                        <div class="content-type-options">
                            <label class="type-option">
                                <input type="radio" name="contentType" value="all" checked>
                                All
                            </label>
                            <label class="type-option">
                                <input type="radio" name="contentType" value="movie">
                                Movie
                            </label>
                            <label class="type-option">
                                <input type="radio" name="contentType" value="anime">
                                Anime
                            </label>
                            <label class="type-option">
                                <input type="radio" name="contentType" value="tv-show">
                                TV Show
                            </label>
                        </div>
                    </div>
                    
                    <div class="filter-section">
                        <h4>Sort By</h4>
                        <div class="sort-options">
                            <label class="sort-option">
                                <input type="radio" name="sortBy" value="relevance" checked>
                                Relevance
                            </label>
                            <label class="sort-option">
                                <input type="radio" name="sortBy" value="top-imdb">
                                Top IMDb
                            </label>
                            <label class="sort-option">
                                <input type="radio" name="sortBy" value="latest">
                                Latest Updates
                            </label>
                        </div>
                    </div>
                    
                    <div class="filter-section">
                        <h4>Genres</h4>
                        <div class="genre-grid">
                            ${this.getGenreCheckboxes()}
                        </div>
                    </div>
                    
                    <div class="filter-actions">
                        <button class="clear-btn">Clear All</button>
                        <button class="apply-btn">Apply Filters</button>
                    </div>
                </div>
            </div>
            
            <div id="${this.config.resultsContainer}" class="search-results-container">
                <div id="${this.config.resultsList}" class="search-results-list"></div>
                <div class="search-footer">
                    <button id="${this.config.viewAllBtn}" class="view-all-btn">
                        View All Results
                        <svg width="16" height="16" viewBox="0 0 16 16" fill="none">
                            <path d="M6 12L10 8L6 4" stroke="currentColor" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
                        </svg>
                    </button>
                </div>
            </div>
        `;

        // Insert search box after the search icon
        const searchIcon = document.getElementById(this.config.searchIcon);
        if (searchIcon) {
            searchIcon.parentNode.insertBefore(searchBox, searchIcon.nextSibling);
        } else {
            document.body.appendChild(searchBox);
        }
    }

    /**
     * Get HTML for genre checkboxes
     */
    getGenreCheckboxes() {
        const genres = [
            "Action", "Adventure", "Thriller", "Drama", "Anime", "Animation", 
            "Comedy", "Crime", "Fantasy", "Horror", "Romance", "Sci-Fi",
            "Mystery", "Documentary", "Family", "Music", "War", "Western"
        ];

        return genres.map(genre => `
            <label class="genre-checkbox">
                <input type="checkbox" value="${genre.toLowerCase()}">
                <span class="checkmark"></span>
                ${genre}
            </label>
        `).join('');
    }

    /**
     * Initialize filter dropdown
     */
    initializeFilterDropdown() {
        // Content type change
        document.querySelectorAll('input[name="contentType"]').forEach(radio => {
            radio.addEventListener('change', (e) => {
                this.selectedContentType = e.target.value;
                this.performSearch();
            });
        });

        // Sort by change
        document.querySelectorAll('input[name="sortBy"]').forEach(radio => {
            radio.addEventListener('change', (e) => {
                this.sortBy = e.target.value;
                this.performSearch();
            });
        });
    }

    /**
     * Set up event listeners for search functionality
     */
    setupEventListeners() {
        const searchIcon = document.getElementById(this.config.searchIcon);
        const searchBox = document.getElementById(this.config.searchBox);
        const searchInput = document.getElementById(this.config.searchInput);
        const filterBtn = document.getElementById(this.config.filterBtn);
        const filterDropdown = document.getElementById(this.config.filterDropdown);
        const viewAllBtn = document.getElementById(this.config.viewAllBtn);

        // Search icon click
        if (searchIcon) {
            searchIcon.addEventListener('click', (e) => {
                this.toggleSearchBox();
                e.stopPropagation();
            });
        }

        // Search input with debounce
        if (searchInput) {
            searchInput.addEventListener('input', (e) => {
                this.handleSearchInput(e.target.value);
            });

            searchInput.addEventListener('keyup', (e) => {
                if (e.key === 'Enter') {
                    this.performSearch();
                }
            });
        }

        // Filter button
        if (filterBtn) {
            filterBtn.addEventListener('click', (e) => {
                this.toggleFilterDropdown();
                e.stopPropagation();
            });
        }

        // View all results
        if (viewAllBtn) {
            viewAllBtn.addEventListener('click', () => {
                this.showAllResults();
            });
        }

        // Genre checkboxes
        const genreGrid = document.querySelector('.genre-grid');
        if (genreGrid) {
            genreGrid.addEventListener('change', (e) => {
                if (e.target.type === 'checkbox') {
                    if (e.target.checked) {
                        this.selectedGenres.add(e.target.value);
                    } else {
                        this.selectedGenres.delete(e.target.value);
                    }
                    this.performSearch();
                }
            });
        }

        // Clear filters
        const clearBtn = document.querySelector('.clear-btn');
        if (clearBtn) {
            clearBtn.addEventListener('click', () => {
                this.clearFilters();
            });
        }

        // Apply filters
        const applyBtn = document.querySelector('.apply-btn');
        if (applyBtn) {
            applyBtn.addEventListener('click', () => {
                this.applyFilters();
            });
        }

        // Close dropdowns when clicking outside
        document.addEventListener('click', (e) => {
            this.handleOutsideClick(e);
        });

        // Keyboard shortcuts
        document.addEventListener('keydown', (e) => {
            // Ctrl+K or Cmd+K for search
            if ((e.ctrlKey || e.metaKey) && e.key === 'k') {
                e.preventDefault();
                this.toggleSearchBox();
            }
            // Escape to close search
            if (e.key === 'Escape' && this.isSearchOpen) {
                this.closeSearchBox();
            }
        });
    }

    /**
     * Toggle search box visibility
     */
    toggleSearchBox() {
        const searchBox = document.getElementById(this.config.searchBox);
        const searchInput = document.getElementById(this.config.searchInput);
        
        if (searchBox.style.display === 'block') {
            this.closeSearchBox();
        } else {
            this.openSearchBox();
        }
    }

    /**
     * Open the search box
     */
    openSearchBox() {
        const searchBox = document.getElementById(this.config.searchBox);
        const searchInput = document.getElementById(this.config.searchInput);
        
        if (searchBox) {
            searchBox.style.display = 'block';
            this.isSearchOpen = true;
            
            // Focus input after animation
            setTimeout(() => {
                if (searchInput) {
                    searchInput.focus();
                }
            }, 10);
        }
    }

    /**
     * Close the search box
     */
    closeSearchBox() {
        const searchBox = document.getElementById(this.config.searchBox);
        const filterDropdown = document.getElementById(this.config.filterDropdown);
        
        if (searchBox) {
            searchBox.style.display = 'none';
            this.isSearchOpen = false;
            
            if (filterDropdown) {
                filterDropdown.style.display = 'none';
            }
            
            // Clear search
            const searchInput = document.getElementById(this.config.searchInput);
            if (searchInput) {
                searchInput.value = '';
            }
            this.clearResults();
        }
    }

    /**
     * Toggle filter dropdown
     */
    toggleFilterDropdown() {
        const filterDropdown = document.getElementById(this.config.filterDropdown);
        if (filterDropdown) {
            filterDropdown.style.display = 
                filterDropdown.style.display === 'block' ? 'none' : 'block';
        }
    }

    /**
     * Handle search input with debounce
     */
    handleSearchInput(value) {
        this.currentSearch = value.trim();
        
        clearTimeout(this.debounceTimer);
        
        if (this.currentSearch.length > 0) {
            this.debounceTimer = setTimeout(() => {
                this.performSearch();
            }, this.config.debounceDelay);
        } else {
            this.clearResults();
        }
    }

    /**
     * Perform the main search
     */
    performSearch() {
        if (!this.isLoaded || !this.currentSearch) {
            this.clearResults();
            return;
        }

        const searchTerm = this.currentSearch.toLowerCase();
        const selectedGenres = Array.from(this.selectedGenres);

        // Filter posts
        let results = this.searchIndex.filter(post => {
            // Title match
            const titleMatch = post.searchableTitles.some(title => 
                title.includes(searchTerm)
            );
            
            // Content type match
            const contentTypeMatch = this.selectedContentType === 'all' || 
                post.contentType.toLowerCase() === this.selectedContentType;
            
            // Genre match
            const genreMatch = selectedGenres.length === 0 || 
                selectedGenres.some(genre => 
                    post.genres.some(g => g.toLowerCase().includes(genre))
                );
            
            return titleMatch && contentTypeMatch && genreMatch;
        });

        // Sort results
        results = this.sortResults(results);

        // Display limited results
        this.displayResults(results.slice(0, this.config.maxResults));
    }

    /**
     * Sort results based on selected criteria
     */
    sortResults(results) {
        switch (this.sortBy) {
            case 'top-imdb':
                return results.sort((a, b) => (b.rating || 0) - (a.rating || 0));
            case 'latest':
                return results.sort((a, b) => {
                    const dateA = new Date(a.dateAdded || 0);
                    const dateB = new Date(b.dateAdded || 0);
                    return dateB - dateA;
                });
            case 'relevance':
            default:
                return results.sort((a, b) => {
                    // Simple relevance scoring
                    const scoreA = this.calculateRelevance(a, this.currentSearch);
                    const scoreB = this.calculateRelevance(b, this.currentSearch);
                    return scoreB - scoreA;
                });
        }
    }

    /**
     * Calculate relevance score for a post
     */
    calculateRelevance(post, searchTerm) {
        let score = 0;
        
        // Exact title match gets highest score
        if (post.title && post.title.toLowerCase().includes(searchTerm)) {
            score += 100;
        }
        
        // Partial title match
        if (post.title && post.title.toLowerCase().indexOf(searchTerm) > -1) {
            score += 50;
        }
        
        // Alternative title match
        if (post.searchableTitles.some(title => title.includes(searchTerm))) {
            score += 30;
        }
        
        // Genre match bonus
        if (this.selectedGenres.size > 0) {
            const genreMatchCount = Array.from(this.selectedGenres).filter(genre =>
                post.genres.some(g => g.toLowerCase().includes(genre))
            ).length;
            score += genreMatchCount * 20;
        }
        
        // Popularity bonus
        score += (post.popularity || 0) / 10;
        
        return score;
    }

    /**
     * Display search results
     */
    displayResults(results) {
        const resultsList = document.getElementById(this.config.resultsList);
        const viewAllBtn = document.getElementById(this.config.viewAllBtn);
        const resultsContainer = document.getElementById(this.config.resultsContainer);

        if (!resultsList || !resultsContainer) return;

        if (results.length === 0) {
            resultsList.innerHTML = this.getNoResultsHTML();
            viewAllBtn.style.display = 'none';
        } else {
            resultsList.innerHTML = results.map(post => this.getResultItemHTML(post)).join('');
            viewAllBtn.style.display = 'block';
        }

        // Show results container
        resultsContainer.style.display = 'block';
    }

    /**
     * Show all results in a dedicated page
     */
    showAllResults() {
        // Store search parameters in sessionStorage
        sessionStorage.setItem('searchQuery', this.currentSearch);
        sessionStorage.setItem('selectedGenres', JSON.stringify(Array.from(this.selectedGenres)));
        sessionStorage.setItem('contentType', this.selectedContentType);
        sessionStorage.setItem('sortBy', this.sortBy);

        // Navigate to search results page
        window.location.href = 'search-results.html';
    }

    /**
     * Get HTML for no results state
     */
    getNoResultsHTML() {
        return `
            <div class="no-results">
                <svg width="64" height="64" viewBox="0 0 24 24" fill="none">
                    <path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm1 15h-2v-2h2v2zm0-4h-2V7h2v6z" fill="#666"/>
                </svg>
                <h3>No results found</h3>
                <p>Try different search terms or adjust your filters</p>
            </div>
        `;
    }

    /**
     * Get HTML for a single result item
     */
    getResultItemHTML(post) {
        // Use actual poster image or placeholder
        const posterImage = post.poster || this.config.placeholderImage;
        
        // Format metadata
        const metadata = [
            post.type || 'Unknown',
            post.year || '?',
            post.duration || ''
        ].filter(Boolean).join(' • ');

        return `
            <a href="${post.streamingUrl || '#'}" class="result-item" data-id="${post.id}">
                <div class="result-thumbnail">
                    <img src="${posterImage}" 
                         alt="${post.title}"
                         onerror="this.onerror=null; this.src='${this.config.placeholderImage}'">
                </div>
                <div class="result-content">
                    <h4 class="result-title">${this.highlightText(post.title, this.currentSearch)}</h4>
                    <div class="result-meta">${metadata}</div>
                    <div class="result-genres">
                        ${(post.genres || []).slice(0, 3).map(genre => 
                            `<span class="result-genre">${genre}</span>`
                        ).join('')}
                    </div>
                    ${post.rating ? `<div class="result-rating">★ ${post.rating}</div>` : ''}
                </div>
            </a>
        `;
    }

    /**
     * Highlight search terms in text
     */
    highlightText(text, searchTerm) {
        if (!text || !searchTerm) return text;
        const regex = new RegExp(`(${searchTerm})`, 'gi');
        return text.replace(regex, '<span class="search-highlight">$1</span>');
    }

    /**
     * Clear all filters
     */
    clearFilters() {
        this.selectedGenres.clear();
        this.selectedContentType = 'all';
        this.sortBy = 'relevance';

        // Reset UI
        document.querySelectorAll('.genre-checkbox input').forEach(cb => {
            cb.checked = false;
        });
        document.querySelector('input[name="contentType"][value="all"]').checked = true;
        document.querySelector('input[name="sortBy"][value="relevance"]').checked = true;
        
        this.performSearch();
    }

    /**
     * Apply filters and close dropdown
     */
    applyFilters() {
        const filterDropdown = document.getElementById(this.config.filterDropdown);
        if (filterDropdown) {
            filterDropdown.style.display = 'none';
        }
        this.performSearch();
    }

    /**
     * Clear search results
     */
    clearResults() {
        const resultsList = document.getElementById(this.config.resultsList);
        const resultsContainer = document.getElementById(this.config.resultsContainer);
        const viewAllBtn = document.getElementById(this.config.viewAllBtn);

        if (resultsList) {
            resultsList.innerHTML = '';
        }
        if (resultsContainer) {
            resultsContainer.style.display = 'none';
        }
        if (viewAllBtn) {
            viewAllBtn.style.display = 'none';
        }
    }

    /**
     * Handle outside click to close dropdowns
     */
    handleOutsideClick(e) {
        const searchBox = document.getElementById(this.config.searchBox);
        const searchIcon = document.getElementById(this.config.searchIcon);
        const filterDropdown = document.getElementById(this.config.filterDropdown);
        const filterBtn = document.getElementById(this.config.filterBtn);

        // Close search box if clicking outside
        if (this.isSearchOpen && searchBox && !searchBox.contains(e.target) && 
            searchIcon && !searchIcon.contains(e.target)) {
            this.closeSearchBox();
        }

        // Close filter dropdown if clicking outside
        if (filterDropdown && filterDropdown.style.display === 'block' &&
            !filterDropdown.contains(e.target) && 
            filterBtn && !filterBtn.contains(e.target)) {
            filterDropdown.style.display = 'none';
        }
    }

    /**
     * Inject styles for the search component
     */
    injectStyles() {
        const style = document.createElement('style');
        style.textContent = `
            /* Compact Search Box */
            .compact-search-box {
                display: none;
                position: absolute;
                top: 100%;
                right: 0;
                width: 450px;
                background: #1a283b;
                border-radius: 12px;
                box-shadow: 0 10px 25px rgba(0, 0, 0, 0.5);
                z-index: 1000;
                overflow: hidden;
                border: 1px solid #2d3748;
                animation: slideDown 0.2s ease-out;
            }

            @keyframes slideDown {
                from {
                    opacity: 0;
                    transform: translateY(-10px);
                }
                to {
                    opacity: 1;
                    transform: translateY(0);
                }
            }

            /* Search Header */
            .search-header {
                padding: 15px;
                border-bottom: 1px solid #2d3748;
            }

            .search-input-wrapper {
                display: flex;
                gap: 10px;
                align-items: center;
            }

            .search-input {
                flex: 1;
                padding: 10px 15px;
                background: rgba(255, 255, 255, 0.1);
                border: 1px solid #4a5568;
                border-radius: 8px;
                color: white;
                font-size: 14px;
                outline: none;
                transition: all 0.3s ease;
            }

            .search-input:focus {
                border-color: #667eea;
                background: rgba(255, 255, 255, 0.15);
            }

            .search-input::placeholder {
                color: #a0aec0;
            }

            /* Filter Button */
            .filter-btn {
                display: flex;
                align-items: center;
                gap: 6px;
                padding: 8px 15px;
                background: rgba(255, 255, 255, 0.1);
                border: 1px solid #4a5568;
                border-radius: 20px;
                color: #cbd5e0;
                font-size: 13px;
                font-weight: 500;
                cursor: pointer;
                transition: all 0.3s ease;
                white-space: nowrap;
            }

            .filter-btn:hover {
                background: rgba(255, 255, 255, 0.15);
                border-color: #667eea;
            }

            .filter-btn svg {
                width: 14px;
                height: 14px;
            }

            /* Filter Dropdown */
            .filter-dropdown {
                display: none;
                position: absolute;
                top: 100%;
                right: 0;
                width: 300px;
                background: #1a283b;
                border-radius: 8px;
                margin-top: 10px;
                padding: 15px;
                box-shadow: 0 10px 25px rgba(0, 0, 0, 0.5);
                border: 1px solid #2d3748;
                z-index: 1001;
                max-height: 400px;
                overflow-y: auto;
            }

            .filter-section {
                margin-bottom: 15px;
            }

            .filter-section h4 {
                color: #e2e8f0;
                font-size: 13px;
                font-weight: 600;
                margin-bottom: 10px;
                text-transform: uppercase;
                letter-spacing: 0.5px;
            }

            /* Content Type Options */
            .content-type-options {
                display: grid;
                grid-template-columns: repeat(2, 1fr);
                gap: 8px;
                margin-bottom: 15px;
            }

            .type-option {
                display: flex;
                align-items: center;
                gap: 6px;
                padding: 6px 10px;
                background: rgba(255, 255, 255, 0.05);
                border-radius: 6px;
                color: #a0aec0;
                font-size: 13px;
                cursor: pointer;
                transition: all 0.3s ease;
            }

            .type-option:hover {
                background: rgba(255, 255, 255, 0.1);
            }

            .type-option input[type="radio"] {
                margin: 0;
                width: 14px;
                height: 14px;
            }

            /* Sort Options */
            .sort-options {
                display: grid;
                grid-template-columns: repeat(2, 1fr);
                gap: 8px;
                margin-bottom: 15px;
            }

            .sort-option {
                display: flex;
                align-items: center;
                gap: 6px;
                padding: 6px 10px;
                background: rgba(255, 255, 255, 0.05);
                border-radius: 6px;
                color: #a0aec0;
                font-size: 13px;
                cursor: pointer;
                transition: all 0.3s ease;
            }

            .sort-option:hover {
                background: rgba(255, 255, 255, 0.1);
            }

            .sort-option input[type="radio"] {
                margin: 0;
                width: 14px;
                height: 14px;
            }

            /* Genre Grid */
            .genre-grid {
                display: grid;
                grid-template-columns: repeat(3, 1fr);
                gap: 8px;
                max-height: 200px;
                overflow-y: auto;
                padding-right: 5px;
            }

            .genre-checkbox {
                display: flex;
                align-items: center;
                gap: 6px;
                padding: 6px 8px;
                background: rgba(255, 255, 255, 0.05);
                border-radius: 6px;
                color: #a0aec0;
                font-size: 12px;
                cursor: pointer;
                transition: all 0.3s ease;
            }

            .genre-checkbox:hover {
                background: rgba(255, 255, 255, 0.1);
            }

            .genre-checkbox input[type="checkbox"] {
                margin: 0;
                width: 14px;
                height: 14px;
            }

            .checkmark {
                width: 14px;
                height: 14px;
                border: 1px solid #4a5568;
                border-radius: 3px;
                display: inline-block;
                position: relative;
            }

            .genre-checkbox input:checked + .checkmark {
                background: #667eea;
                border-color: #667eea;
            }

            .genre-checkbox input:checked + .checkmark::after {
                content: '✓';
                position: absolute;
                top: 50%;
                left: 50%;
                transform: translate(-50%, -50%);
                color: white;
                font-size: 10px;
                font-weight: bold;
            }

            /* Filter Actions */
            .filter-actions {
                display: flex;
                gap: 10px;
                margin-top: 15px;
                padding-top: 15px;
                border-top: 1px solid #2d3748;
            }

            .clear-btn, .apply-btn {
                flex: 1;
                padding: 8px 15px;
                border-radius: 6px;
                font-size: 13px;
                font-weight: 500;
                cursor: pointer;
                transition: all 0.3s ease;
                border: none;
            }

            .clear-btn {
                background: rgba(255, 255, 255, 0.05);
                color: #a0aec0;
            }

            .clear-btn:hover {
                background: rgba(255, 255, 255, 0.1);
            }

            .apply-btn {
                background: #667eea;
                color: white;
            }

            .apply-btn:hover {
                background: #5a67d8;
            }

            /* Search Results */
            .search-results-container {
                display: none;
                max-height: 500px;
                overflow-y: auto;
            }

            .search-results-list {
                padding: 10px;
            }

            /* Result Item */
            .result-item {
                display: flex;
                gap: 12px;
                padding: 10px;
                border-radius: 8px;
                text-decoration: none;
                color: inherit;
                transition: all 0.3s ease;
                margin-bottom: 5px;
            }

            .result-item:hover {
                background: rgba(255, 255, 255, 0.05);
            }

            .result-thumbnail {
                width: 60px;
                height: 90px;
                flex-shrink: 0;
            }

            .result-thumbnail img {
                width: 100%;
                height: 100%;
                object-fit: cover;
                border-radius: 6px;
            }

            .result-content {
                flex: 1;
                min-width: 0;
            }

            .result-title {
                color: white;
                font-size: 14px;
                font-weight: 600;
                margin-bottom: 4px;
                line-height: 1.3;
            }

            .result-meta {
                color: #a0aec0;
                font-size: 12px;
                margin-bottom: 6px;
            }

            .result-genres {
                display: flex;
                gap: 5px;
                flex-wrap: wrap;
                margin-bottom: 4px;
            }

            .result-genre {
                font-size: 10px;
                padding: 2px 6px;
                background: rgba(102, 126, 234, 0.1);
                color: #9ab1ff;
                border-radius: 10px;
                border: 1px solid rgba(102, 126, 234, 0.2);
            }

            .result-rating {
                color: #ffd700;
                font-size: 12px;
                font-weight: 500;
            }

            /* Search Highlight */
            .search-highlight {
                background: rgba(78, 205, 196, 0.3);
                color: #4ecdc4;
                font-weight: 600;
                padding: 0 2px;
                border-radius: 3px;
            }

            /* Search Footer */
            .search-footer {
                padding: 15px;
                border-top: 1px solid #2d3748;
                text-align: center;
            }

            .view-all-btn {
                display: inline-flex;
                align-items: center;
                gap: 6px;
                padding: 8px 20px;
                background: rgba(102, 126, 234, 0.1);
                border: 1px solid rgba(102, 126, 234, 0.3);
                border-radius: 20px;
                color: #9ab1ff;
                font-size: 13px;
                font-weight: 500;
                cursor: pointer;
                transition: all 0.3s ease;
            }

            .view-all-btn:hover {
                background: rgba(102, 126, 234, 0.2);
                border-color: #667eea;
            }

            .view-all-btn svg {
                width: 14px;
                height: 14px;
            }

            /* No Results */
            .no-results {
                text-align: center;
                padding: 40px 20px;
                color: #a0aec0;
            }

            .no-results svg {
                margin-bottom: 15px;
                opacity: 0.5;
            }

            .no-results h3 {
                color: #e2e8f0;
                font-size: 16px;
                margin-bottom: 8px;
            }

            .no-results p {
                font-size: 13px;
            }

            /* Scrollbar */
            ::-webkit-scrollbar {
                width: 6px;
            }

            ::-webkit-scrollbar-track {
                background: rgba(255, 255, 255, 0.05);
                border-radius: 3px;
            }

            ::-webkit-scrollbar-thumb {
                background: rgba(255, 255, 255, 0.1);
                border-radius: 3px;
            }

            ::-webkit-scrollbar-thumb:hover {
                background: rgba(255, 255, 255, 0.2);
            }

            /* Mobile Responsive */
            @media (max-width: 768px) {
                .compact-search-box {
                    width: 350px;
                    right: -50px;
                }

                .filter-dropdown {
                    width: 280px;
                }

                .genre-grid {
                    grid-template-columns: repeat(2, 1fr);
                }

                .content-type-options,
                .sort-options {
                    grid-template-columns: 1fr;
                }
            }

            @media (max-width: 480px) {
                .compact-search-box {
                    width: 320px;
                    right: -80px;
                }

                .result-thumbnail {
                    width: 50px;
                    height: 75px;
                }

                .result-title {
                    font-size: 13px;
                }

                .result-meta {
                    font-size: 11px;
                }
            }
        `;
        document.head.appendChild(style);
    }

    /**
     * Handle load errors
     */
    handleLoadError(error) {
        const resultsContainer = document.getElementById(this.config.resultsContainer);
        if (resultsContainer) {
            resultsContainer.innerHTML = `
                <div class="no-results">
                    <h3>⚠️ Search Unavailable</h3>
                    <p>Unable to load content. Please try again later.</p>
                </div>
            `;
            resultsContainer.style.display = 'block';
        }
    }

    /**
     * Clear search cache
     */
    clearCache() {
        this.searchCache.clear();
        console.log('🗑️ Search cache cleared');
    }

    /**
     * Refresh data
     */
    async refreshData() {
        this.searchCache.clear();
        await this.loadContent();
        console.log('🔄 Search data refreshed');
    }

    /**
     * Get search stats
     */
    getStats() {
        return {
            loadedPosts: this.allPosts.length,
            selectedGenres: this.selectedGenres.size,
            currentSearch: this.currentSearch,
            contentType: this.selectedContentType,
            sortBy: this.sortBy
        };
    }

    /**
     * Destroy component
     */
    destroy() {
        this.searchCache.clear();
        this.allPosts = [];
        this.isLoaded = false;
        console.log('🗑️ Compact Global Search destroyed');
    }
}

// Auto-initialize
if (typeof window !== 'undefined') {
    window.GlobalSearch = GlobalSearch;
    
    document.addEventListener('DOMContentLoaded', () => {
        if (document.getElementById('searchIcon')) {
            window.globalSearch = new GlobalSearch({
                dataUrl: 'data/posts.json'
            });
        }
    });
}