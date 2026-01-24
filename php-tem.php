1. MAIN CONTENT TABLE (content)
All common fields for movies/series:
sql code:
CREATE TABLE content (
    -- Core Identification
    id VARCHAR(50) PRIMARY KEY,
    slug VARCHAR(100) UNIQUE NOT NULL,
    
    -- Titles & Search
    title VARCHAR(200) NOT NULL,
    original_title VARCHAR(200),
    japanese_title VARCHAR(200),
    searchable_title VARCHAR(500),
    
    -- Basic Info
    content_type ENUM('movie', 'tv', 'anime', 'drama') NOT NULL,
    category VARCHAR(50),
    description TEXT,
    
    -- Dates & Status
    aired_year INT,
    premiered VARCHAR(100),
    date_added DATE NOT NULL,
    status ENUM('upcoming', 'airing', 'finished', 'cancelled') NOT NULL,
    
    -- Duration
    duration_minutes INT,                    -- For movies
    episode_duration_minutes INT,            -- For series
    
    -- Ratings & Scores
    rating DECIMAL(3,1),
    mal_score DECIMAL(4,2),
    imdb_score DECIMAL(3,1),
    popularity INT DEFAULT 0,
    
    -- Media URLs
    poster_url VARCHAR(500),
    backdrop_url VARCHAR(500),
    trailer_url VARCHAR(500),
    
    -- Production Info
    studio VARCHAR(100),
    country VARCHAR(50),
    certification VARCHAR(20),               -- e.g., "TV-14", "R"
    badge ENUM('HD', '4K', 'R', '18+', 'PG', NULL),
    
    -- Flags
    featured BOOLEAN DEFAULT FALSE,
    
    -- Timestamps
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
2. SERIES INFO TABLE (series_info)
For TV/anime/drama only:
CREATE TABLE series_info (
    content_id VARCHAR(50) PRIMARY KEY,
    total_seasons INT DEFAULT 1,
    total_episodes INT,                      -- <-- FUTURE FIELD
    
    -- Episode scheduling
    airing_schedule ENUM('weekly', 'daily', 'monthly', 'completed', 'irregular'),
    next_air_date DATE,
    next_air_time TIME,
    
    FOREIGN KEY (content_id) REFERENCES content(id) ON DELETE CASCADE
);
3. SEASONS TABLE (seasons)
sql code:
CREATE TABLE seasons (
    id INT AUTO_INCREMENT PRIMARY KEY,
    content_id VARCHAR(50) NOT NULL,
    season_number INT NOT NULL,
    season_name VARCHAR(100),
    year INT,
    episode_count INT,
    premiered_date DATE,
    mal_score DECIMAL(4,2),
    
    UNIQUE KEY (content_id, season_number),
    FOREIGN KEY (content_id) REFERENCES content(id) ON DELETE CASCADE
);
4. EPISODES TABLE (episodes)
With FUTURE airing fields:
sql code: 
CREATE TABLE episodes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    season_id INT NOT NULL,
    episode_number INT NOT NULL,
    title VARCHAR(200) NOT NULL,
    japanese_title VARCHAR(200),
    description TEXT,
    duration_minutes INT,
    
    -- FUTURE: Airing schedule
    air_date DATE,
    air_time TIME,
    release_date DATE,
    
    -- Metadata
    thumbnail_url VARCHAR(500),
    
    UNIQUE KEY (season_id, episode_number),
    FOREIGN KEY (season_id) REFERENCES seasons(id) ON DELETE CASCADE
);
5. VIDEO SERVERS TABLE (episode_servers) - EXPANDED VERSION
COMPLETE with ALL link types:
sql code:
CREATE TABLE episode_servers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    episode_id INT NOT NULL,
    
    -- Server Type (RAW, SUB, DUB)
    server_type ENUM('raw', 'sub', 'dub') NOT NULL,
    
    -- Server Quality (MUST be HD-01 to HD-05)
    server_name ENUM('HD-01', 'HD-02', 'HD-03', 'HD-04', 'HD-05') NOT NULL,
    
    -- ALL VIDEO LINK TYPES:
    direct_link TEXT,                       -- Direct video file URL
    embed_code TEXT,                        -- HTML embed code (iframe)
    embed_link_short_and_long TEXT,         -- URL for embedding
    watch_page_long_link TEXT,              -- Direct watch page
    watch_page_short_link                   -- Direct watch page
    public_page_link TEXT,                  -- Public video page
    short_link VARCHAR(500),                -- Shortened URL
    full_link TEXT,                         -- Full/long URL
    download_page_link TEXT,                -- Download page
    
    -- Additional Info
    language VARCHAR(50),                   -- e.g., 'Japanese', 'Native languahe (Raw)', 'English'
    quality ENUM('480p', '720p', '1080p', '4K'),
    server_provider VARCHAR(100),           -- e.g., 'Filemoon', 'Vidstream', 'Vidcloud', 'mixdrop', 'Byse', 'Streamup'. 'Voe', 'Streamgh', 'screenpal', 'Savefiles',
    
    UNIQUE KEY (episode_id, server_type, server_name),
    FOREIGN KEY (episode_id) REFERENCES episodes(id) ON DELETE CASCADE
      
);
6. ADDITIONAL TABLES Synonyms Table:
Sql code:
CREATE TABLE synonyms (
    id INT AUTO_INCREMENT PRIMARY KEY,
    content_id VARCHAR(50) NOT NULL,
    synonym VARCHAR(200) NOT NULL,
    UNIQUE KEY (content_id, synonym),
    FOREIGN KEY (content_id) REFERENCES content(id) ON DELETE CASCADE
);
Genres Table:
Sql code:
      CREATE TABLE genres (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) UNIQUE NOT NULL
);

CREATE TABLE content_genres (
    content_id VARCHAR(50),
    genre_id INT,
    PRIMARY KEY (content_id, genre_id),
    FOREIGN KEY (content_id) REFERENCES content(id) ON DELETE CASCADE,
    FOREIGN KEY (genre_id) REFERENCES genres(id) ON DELETE CASCADE
);
People Table (Cast & Crew):
      CREATE TABLE people (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    role ENUM('voice_actor', 'actor', 'director', 'producer', 'writer'),
    UNIQUE KEY (name, role)
);

CREATE TABLE content_people (
    id INT AUTO_INCREMENT PRIMARY KEY,
    content_id VARCHAR(50),
    person_id INT,
    character_name VARCHAR(100),
    role_type ENUM('cast', 'producer', 'director'),
    FOREIGN KEY (content_id) REFERENCES content(id) ON DELETE CASCADE,
    FOREIGN KEY (person_id) REFERENCES people(id) ON DELETE CASCADE
);
Producers Table:
Sql code:
      CREATE TABLE producers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) UNIQUE NOT NULL
);

CREATE TABLE content_producers (
    content_id VARCHAR(50),
    producer_id INT,
    PRIMARY KEY (content_id, producer_id),
    FOREIGN KEY (content_id) REFERENCES content(id) ON DELETE CASCADE,
    FOREIGN KEY (producer_id) REFERENCES producers(id) ON DELETE CASCADE
);
      
STEP-BY-STEP CONVERSION GUIDE FOR you:
STEP 1: Process Main Content:
Sql code:
-- 1. Insert into MAIN CONTENT table
INSERT INTO content (
    id, slug, title, original_title, japanese_title,
    searchable_title, aired_year, premiered, date_added,
    content_type, featured, rating, category,
    duration_minutes, episode_duration_minutes, status,
    description, poster_url, backdrop_url, trailer_url,
    mal_score, imdb_score, popularity,
    studio, country, certification, badge
) VALUES (
    'mha-s1',
    'my-hero-academia-season-1',
    'My Hero Academia Season 1',
    'Boku no Hero Academia',
    '僕のヒーローアカデミア',
    'My Hero Academia Season 1 Boku no Hero Academia 僕のヒーローアカデミア MHA Season 1 Boku no Hero Academia S1',
    2016,
    'Spring 2016',
    '2024-12-16',
    'anime',
    FALSE,
    8.0,
    'action',
    NULL,  -- duration_minutes (not for series)
    24,    -- episode_duration_minutes
    'finished',
    'In a world where 80% of humanity possesses ''Quirks,'' Izuku Midoriya is born powerless but gains a chance to become a hero after a fated meeting with All Might.',
    'https://cdn.myanimelist.net/images/anime/10/78745l.jpg',
    'https://image.tmdb.org/t/p/original/6v6pBvM6oXG7WpYm8M9r8R0R6j.jpg',
    'https://www.youtube.com/watch?v=-77UEct0K7Q',
    7.96,
    8.4,
    99,
    'Bones',
    'Japan',
    'TV-14',
    'HD'
);
STEP 2: Process Related Data:
-- 2. Insert SYNONYMS
INSERT INTO synonyms (content_id, synonym) VALUES
    ('mha-s1', 'MHA Season 1'),
    ('mha-s1', 'Boku no Hero Academia S1');

-- 3. Insert GENRES
INSERT IGNORE INTO genres (name) VALUES 
    ('Super Hero'), ('Action'), ('Fantasy'), ('School');
    
INSERT INTO content_genres (content_id, genre_id) 
SELECT 'mha-s1', id FROM genres 
WHERE name IN ('Super Hero', 'Action', 'Fantasy', 'School');

-- 4. Insert PRODUCERS
INSERT IGNORE INTO producers (name) VALUES ('TOHO');
INSERT INTO content_producers (content_id, producer_id) 
SELECT 'mha-s1', id FROM producers WHERE name = 'TOHO';

-- 5. Insert CAST
INSERT IGNORE INTO people (name, role) VALUES 
    ('Daiki Yamashita', 'voice_actor'),
    ('Kenta Miyake', 'voice_actor'),
    ('Nobuhiko Okamoto', 'voice_actor');
    
INSERT INTO content_people (content_id, person_id, character_name, role_type)
SELECT 'mha-s1', id, NULL, 'cast' FROM people 
WHERE name IN ('Daiki Yamashita', 'Kenta Miyake', 'Nobuhiko Okamoto');

STEP 3: Process Series Data (if not movie):
-- 6. Insert into SERIES_INFO
INSERT INTO series_info (content_id, total_seasons, total_episodes)
VALUES ('mha-s1', 1, NULL);

STEP 4: Process Seasons & Episodes:
-- 7. Insert SEASON
INSERT INTO seasons (content_id, season_number, year, episode_count)
VALUES ('mha-s1', 1, 2016, 13);
-- Get the auto-generated season_id (e.g., 1)

-- 8. Insert EPISODE
INSERT INTO episodes (
    season_id, episode_number, title, 
    duration_minutes, release_date
) VALUES (
    1, 1, 'Izuku Midoriya: Origin',
    24, '2024-12-16'
);
-- Get the auto-generated episode_id (e.g., 1)
STEP 5: Process VIDEO SERVERS WITH ALL LINK TYPES
This is the CRITICAL part with HD-01 to HD-05 consistency:

For RAW servers:
  SQL code:
      -- HD-01 Server
INSERT INTO episode_servers (
    episode_id, server_type, server_name,
    direct_link, embed_code, embed_link,
    watch_page_link, public_page_link,
    short_link, full_link, download_page_link,
    language, quality, server_provider
) VALUES (
    1, 'raw', 'HD-01',
    'https://direct.video/file1.mp4',                -- direct_link
    '<iframe src="..."></iframe>',                  -- embed_code
    'https://embed.site/video1',                    -- embed_link
    'https://watch.site/video1',                    -- watch_page_link
    'https://public.site/video1',                   -- public_page_link
    'https://short.url/abc123',                     -- short_link
    'https://verylongurl.com/path/to/video/file1',  -- full_link
    'https://download.site/video1',                 -- download_page_link
    'Japanese', '1080p', 'Filemoon'
);

-- HD-02 Server
INSERT INTO episode_servers (
    episode_id, server_type, server_name,
    direct_link, embed_link, watch_page_link
) VALUES (
    1, 'raw', 'HD-02',
    'https://direct.video/file2.mp4',
    'https://embed.site/video2',
    'https://watch.site/video2'
);

-- HD-03 Server
INSERT INTO episode_servers (
    episode_id, server_type, server_name,
    direct_link, embed_link
) VALUES (
    1, 'raw', 'HD-03',
    'https://server-raw.com/mha-s1-e1-3',
    'https://embed-raw.com/mha-s1-e1-3'
);

-- HD-04 Server (optional - can be NULL)
INSERT INTO episode_servers (
    episode_id, server_type, server_name,
    direct_link
) VALUES (
    1, 'raw', 'HD-04',
    NULL  -- No link yet
);

-- HD-05 Server (optional - can be NULL)
INSERT INTO episode_servers (
    episode_id, server_type, server_name,
    direct_link
) VALUES (
    1, 'raw', 'HD-05',
    NULL  -- No link yet
);
For SUB servers:
      -- SUB HD-01
INSERT INTO episode_servers (
    episode_id, server_type, server_name,
    direct_link, embed_link, watch_page_link
) VALUES (
    1, 'sub', 'HD-01',
    'https://server-sub.com/mha-s1-e1-1',
    'https://embed-sub.com/mha-s1-e1-1',
    'https://watch-sub.com/mha-s1-e1-1'
);

-- SUB HD-02
INSERT INTO episode_servers (
    episode_id, server_type, server_name,
    direct_link, embed_link
) VALUES (
    1, 'sub', 'HD-02',
    'https://server-sub.com/mha-s1-e1-2',
    'https://embed-sub.com/mha-s1-e1-2'
);

-- Continue for HD-03, HD-04, HD-05...
For DUB servers:
      -- DUB HD-01
INSERT INTO episode_servers (
    episode_id, server_type, server_name,
    direct_link, embed_link, watch_page_link
) VALUES (
    1, 'dub', 'HD-01',
    'https://server-dub.com/mha-s1-e1-1',
    'https://embed-dub.com/mha-s1-e1-1',
    'https://watch-dub.com/mha-s1-e1-1'
);
STEP 6: Handle Movies (Special Case):
      
For content_type = 'movie':
Sql code:
-- Movie doesn't get series_info
-- Create one "episode" representing the full movie
INSERT INTO episodes (
    season_id, episode_number, title, duration_minutes
) VALUES (
    NULL, 1, 'Full Movie', 120  -- 2 hour movie
);

-- Movie gets ALL link types in servers
INSERT INTO episode_servers (
    episode_id, server_type, server_name,
    direct_link, embed_code, embed_link,
    watch_page_link, public_page_link,
    short_link, full_link, download_page_link
) VALUES 
-- RAW version
(1, 'raw', 'HD-01', 'movie_raw_direct.mp4', '<iframe>', 'embed_url', 'watch_url', 'public_url', 'short_url', 'full_url', 'download_url'),
(1, 'raw', 'HD-02', 'movie_raw_720p.mp4', NULL, 'embed2', 'watch2', NULL, NULL, NULL, NULL),

-- SUB version  
(1, 'sub', 'HD-01', 'movie_sub_direct.mp4', '<iframe>', 'embed_sub', 'watch_sub', NULL, NULL, NULL, NULL),

-- DUB version
(1, 'dub', 'HD-01', 'movie_dub_direct.mp4', '<iframe', 'embed_dub', NULL, NULL, NULL, NULL, NULL);

SPECIAL INSTRUCTIONS FOR You:
1. SERVER NAME MAPPING RULES:
JSON Server Names → MySQL Server Names
"HD-01" → "HD-01" (keep as-is)
"HD-02" → "HD-02"
"HD-03" → "HD-03"
"server1" → "HD-01" (map to HD-01)
"streamup" → "HD-01" (map to HD-01)
"Filemoon" → "HD-02" (map to HD-02)
"Mixdrop" → "HD-03" (map to HD-03)
2. LINK TYPE DISTRIBUTION:
  sql:
-- When JSON has only "url", distribute it intelligently:
IF JSON.url contains "embed" THEN → embed_link
ELSE IF JSON.url contains "watch" THEN → watch_page_link  
ELSE IF JSON.url contains "download" THEN → download_page_link
ELSE IF JSON.url ends with ".mp4/.m3u8" THEN → direct_link
ELSE → watch_page_link (default)

3. DATA TRANSFORMATION EXAMPLES:
-- JSON duration "24 min" → 24 (INTEGER)
UPDATE content SET episode_duration_minutes = 24 WHERE duration = '24 min';

-- Convert boolean strings
UPDATE content SET featured = CASE 
    WHEN featured = 'true' THEN TRUE 
    WHEN featured = 'false' THEN FALSE 
    ELSE FALSE END;

-- Set badge based on certification
UPDATE content SET badge = CASE
    WHEN certification LIKE '%R%' THEN 'R'
    WHEN certification LIKE '%18+%' THEN '18+'
    WHEN certification LIKE '%HD%' THEN 'HD'
    WHEN certification LIKE '%TV-MA%' THEN 'TV-MA'
    WHEN certification LIKE '%PG-13%' THEN 'PG-13'
    WHEN certification LIKE '%TV-PG%' THEN 'TV-PG'
    WHEN certification LIKE '%TV-G%' THEN 'TV-G'
    ELSE NULL END;

4. FUTURE AIR DATE/TIME PREPARATION:
Sql code:
-- Example for setting future air times
UPDATE episodes SET 
    air_date = '2024-12-25',
    air_time = '20:00:00'
WHERE episode_number = 5 AND season_id = 1;
5. TOTAL EPISODES CALCULATION:
sql:
-- After all episodes inserted
UPDATE series_info s
SET total_episodes = (
    SELECT COUNT(*) 
    FROM episodes e 
    JOIN seasons se ON e.season_id = se.id 
    WHERE se.content_id = s.content_id
);
EXPECTED FINAL OUTPUT FOR QWEN AI
Provide SQL in this order:

Part 1: CREATE TABLES:
-- 1. content
-- 2. series_info  
-- 3. seasons
-- 4. episodes
-- 5. episode_servers (with ALL link types)
-- 6. synonyms
-- 7. genres + content_genres
-- 8. people + content_people
-- 9. producers + content_producers

Part 2: SAMPLE INSERTS (My Hero Academia):
  Sql:
  -- Show complete flow for one anime series
  -- Include ALL server types with HD-01 to HD-05
  
Part 3: UTILITY FUNCTIONS:
sql:
-- Function to calculate total_episodes
-- Function to update airing schedules
-- Function to ensure server consistency
