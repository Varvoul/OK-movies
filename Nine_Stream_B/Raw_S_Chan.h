<style>
    /* Prevent horizontal scrolling and set base styles */
    html, body {
        overflow-x: hidden;
        width: 100%;
        margin: 0;
        padding: 0;
        -webkit-text-size-adjust: 100%;
        -moz-text-size-adjust: 100%;
        text-size-adjust: 100%;
    }
    
    body {
        font-family: 'Inter', sans-serif;
        background-color: #171a29; /* Theme background color */
        color: #e5e7eb;
        min-height: 100vh;
    }
    
    /* Better touch scrolling and tap highlights */
    * {
        -webkit-tap-highlight-color: transparent;
        -webkit-touch-callout: none;
    }
    
    /* Scrollbar styling */
    .hide-scrollbar::-webkit-scrollbar {
        display: none;
    }
    
    .hide-scrollbar {
        -ms-overflow-style: none;
        scrollbar-width: none;
    }
    
    .custom-scrollbar::-webkit-scrollbar {
        width: 4px;
        height: 4px;
    }
    
    .custom-scrollbar::-webkit-scrollbar-track {
        background: rgba(255, 255, 255, 0.05);
        border-radius: 4px;
    }
    
    .custom-scrollbar::-webkit-scrollbar-thumb {
        background: rgba(73, 139, 187, 0.3);
        border-radius: 4px;
    }
    
    .custom-scrollbar::-webkit-scrollbar-thumb:hover {
        background: rgba(73, 139, 187, 0.5);
    }
    
    /* Video Container Responsive */
    .video-container-wrapper {
        position: relative;
        width: 100%;
        padding-bottom: 56.25%; /* 16:9 Aspect Ratio */
        height: 0;
        overflow: hidden;
        border-radius: 0.75rem;
        background: #000;
        box-shadow: 0 4px 12px rgba(0, 0, 0, 0.3);
    }
    
    .video-container {
        position: absolute;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        border: none;
    }
    
    /* Episode list item - mobile optimized */
    .episode-list-item {
        transition: all 0.2s ease;
        border-left: 3px solid transparent;
        padding: 12px 16px;
        border-radius: 8px;
        margin-bottom: 6px;
        background-color: #141a25;
        cursor: pointer;
        color: #e5e7eb;
        font-size: 14px;
        line-height: 1.4;
        word-break: break-word;
        border: 1px solid #2d3347;
    }
    
    @media (max-width: 640px) {
        .episode-list-item {
            padding: 14px 16px;
            font-size: 15px;
        }
    }
    
    .episode-list-item:hover {
        background-color: #1e2533 !important;
        border-left: 3px solid #498BBB;
        transform: translateX(4px);
        box-shadow: 0 2px 8px rgba(73,139,187,0.2);
    }
    
    .episode-list-item.active {
        background-color: #1e2533 !important;
        border-left: 3px solid #498BBB;
        font-weight: 500;
        border-color: #498BBB;
    }
    
    /* Server buttons - mobile optimized */
    .server-btn {
        transition: all 0.15s ease;
        cursor: pointer;
        background-color: #141a25 !important;
        color: #e5e7eb !important;
        border: 1px solid #2d3347;
        padding: 8px 12px;
        font-size: 13px;
        font-weight: 500;
        border-radius: 6px;
        min-width: 60px;
        text-align: center;
        touch-action: manipulation;
    }
    
    @media (max-width: 480px) {
        .server-btn {
            padding: 10px 8px;
            font-size: 12px;
            min-width: 55px;
        }
    }
    
    .server-btn:hover {
        background-color: #1e2533 !important;
        border-color: #498BBB;
    }
    
    .server-btn.active-server {
        background-color: #498BBB !important;
        color: white !important;
        border-color: #498BBB !important;
    }
    
    .server-btn:active {
        transform: scale(0.97);
    }
    
    /* Season button styling - mobile optimized */
    .season-btn {
        transition: all 0.2s ease;
        padding: 10px 16px;
        border-radius: 8px;
        font-weight: 500;
        cursor: pointer;
        border: 1px solid transparent;
        background-color: #141a25 !important;
        color: #e5e7eb;
        font-size: 14px;
        touch-action: manipulation;
        white-space: nowrap;
    }
    
    @media (max-width: 640px) {
        .season-btn {
            padding: 12px 16px;
            font-size: 14px;
            flex: 0 0 auto;
        }
    }
    
    .season-btn.active-season {
        background: #1e2533 !important;
        border-color: #498BBB !important;
        color: #498BBB;
    }
    
    .season-btn:hover:not(.active-season) {
        background: #1e2533 !important;
        border-color: #2d3347;
    }
    
    .season-btn:active {
        transform: scale(0.97);
    }
    
    /* Layout containers */
    .player-section {
        max-width: 1200px;
        margin: 0 auto;
        padding: 12px;
    }
    
    @media (min-width: 640px) {
        .player-section {
            padding: 16px;
        }
    }
    
    @media (min-width: 1024px) {
        .player-section {
            padding: 20px;
        }
    }
    
    .controls-panel {
        background: #171a29;
        border-radius: 16px;
        padding: 16px;
        margin-top: 16px;
        box-shadow: 0 8px 24px rgba(0,0,0,0.4);
        border: 1px solid #2d3347;
        color: #e5e7eb;
    }
    
    @media (min-width: 640px) {
        .controls-panel {
            padding: 20px;
            border-radius: 20px;
        }
    }
    
    @media (min-width: 1024px) {
        .controls-panel {
            padding: 24px;
        }
    }
    
    .section-title {
        font-size: 1rem;
        font-weight: 600;
        margin-bottom: 12px;
        color: #f3f4f6;
    }
    
    @media (min-width: 640px) {
        .section-title {
            font-size: 1.1rem;
            margin-bottom: 16px;
        }
    }
    
    .server-category {
        margin-bottom: 16px;
    }
    
    @media (min-width: 640px) {
        .server-category {
            margin-bottom: 20px;
        }
    }
    
    .server-category-label {
        font-size: 0.75rem;
        font-weight: 700;
        text-transform: uppercase;
        color: #9ca3af;
        margin-bottom: 8px;
        display: block;
        letter-spacing: 0.5px;
    }
    
    @media (min-width: 640px) {
        .server-category-label {
            font-size: 0.8rem;
            margin-bottom: 10px;
        }
    }
    
    .server-buttons-row {
        display: flex;
        flex-wrap: wrap;
        gap: 8px;
    }
    
    @media (max-width: 480px) {
        .server-buttons-row {
            gap: 6px;
        }
    }
    
    .episodes-grid {
        display: flex;
        flex-direction: column;
        gap: 6px;
        max-height: 350px;
        overflow-y: auto;
        padding-right: 8px;
    }
    
    @media (min-width: 640px) {
        .episodes-grid {
            max-height: 400px;
            gap: 8px;
        }
    }
    
    @media (min-width: 1024px) {
        .episodes-grid {
            max-height: 450px;
        }
    }
    
    .seasons-row {
        display: flex;
        flex-wrap: nowrap;
        overflow-x: auto;
        gap: 8px;
        margin-bottom: 20px;
        padding-bottom: 8px;
        -webkit-overflow-scrolling: touch;
        scrollbar-width: thin;
    }
    
    @media (min-width: 640px) {
        .seasons-row {
            flex-wrap: wrap;
            overflow-x: visible;
            gap: 10px;
        }
    }
    
    /* loading overlay */
    .video-loading-overlay {
        position: absolute;
        inset: 0;
        background: rgba(0, 0, 0, 0.8);
        display: flex;
        align-items: center;
        justify-content: center;
        color: white;
        font-size: 1.2rem;
        cursor: pointer;
        backdrop-filter: blur(4px);
        border-radius: 12px;
    }
    
    @media (min-width: 640px) {
        .video-loading-overlay {
            font-size: 1.5rem;
        }
    }
    
    /* Info strip - mobile optimized */
    .current-info {
        display: flex;
        flex-direction: column;
        gap: 12px;
        margin-bottom: 16px;
        font-size: 0.9rem;
        background: #141a25;
        padding: 16px;
        border-radius: 12px;
        color: #d1d5db;
        border: 1px solid #2d3347;
    }
    
    @media (min-width: 640px) {
        .current-info {
            flex-direction: row;
            justify-content: space-between;
            align-items: center;
            gap: 16px;
            padding: 12px 16px;
        }
    }
    
    .info-row {
        display: flex;
        flex-wrap: wrap;
        gap: 12px;
        align-items: center;
    }
    
    @media (min-width: 640px) {
        .info-row {
            gap: 16px;
        }
    }
    
    .info-item {
        display: flex;
        align-items: center;
        background: #171a29;
        padding: 6px 12px;
        border-radius: 20px;
        border: 1px solid #2d3347;
    }
    
    .info-item span:first-child {
        color: #9ca3af;
        margin-right: 6px;
        font-size: 0.8rem;
    }
    
    .info-value {
        font-weight: 600;
        color: #498BBB;
        font-size: 0.9rem;
    }
    
    /* Navigation buttons - mobile optimized */
    .nav-buttons {
        display: flex;
        flex-wrap: wrap;
        gap: 8px;
        align-items: center;
        width: 100%;
    }
    
    @media (min-width: 640px) {
        .nav-buttons {
            width: auto;
            gap: 10px;
        }
    }
    
    .nav-btn {
        background: #141a25;
        border: 1px solid #2d3347;
        color: #e5e7eb;
        padding: 10px 16px;
        border-radius: 8px;
        font-size: 0.9rem;
        font-weight: 500;
        display: flex;
        align-items: center;
        justify-content: center;
        gap: 4px;
        cursor: pointer;
        transition: all 0.2s;
        flex: 1 1 auto;
        touch-action: manipulation;
        min-height: 44px; /* Better touch target */
    }
    
    @media (min-width: 480px) {
        .nav-btn {
            flex: 0 1 auto;
            padding: 8px 20px;
        }
    }
    
    @media (min-width: 640px) {
        .nav-btn {
            min-height: auto;
            padding: 8px 16px;
        }
    }
    
    .nav-btn:hover {
        background: #1e2533;
        border-color: #498BBB;
        color: white;
    }
    
    .nav-btn:active {
        transform: scale(0.96);
    }
    
    /* Add to list button */
    .add-to-list-btn {
        background: #141a25;
        border: 1px solid #498BBB;
        color: #e5e7eb;
        padding: 10px 16px;
        border-radius: 8px;
        font-size: 0.9rem;
        font-weight: 500;
        display: flex;
        align-items: center;
        justify-content: center;
        gap: 4px;
        cursor: pointer;
        transition: all 0.2s;
        flex: 1 1 auto;
        touch-action: manipulation;
        min-height: 44px;
    }
    
    @media (min-width: 480px) {
        .add-to-list-btn {
            flex: 0 1 auto;
            padding: 8px 20px;
        }
    }
    
    @media (min-width: 640px) {
        .add-to-list-btn {
            min-height: auto;
            padding: 8px 16px;
        }
    }
    
    .add-to-list-btn:hover {
        background: #498BBB;
        color: white;
    }
    
    .add-to-list-btn:active {
        transform: scale(0.96);
    }
    
    /* Server message */
    .server-message {
        font-size: 0.85rem;
        color: #fcd34d;
        background: rgba(20, 26, 37, 0.95);
        padding: 12px 16px;
        border-radius: 10px;
        margin-bottom: 16px;
        border-left: 4px solid #fbbf24;
        border: 1px solid #2d3347;
        line-height: 1.5;
    }
    
    @media (min-width: 640px) {
        .server-message {
            font-size: 0.9rem;
            padding: 12px 20px;
        }
    }
    
    /* Helper note */
    .helper-note {
        font-size: 0.75rem;
        color: #9ca3af;
        margin-top: 16px;
        text-align: center;
        padding: 8px;
        background: #141a25;
        border-radius: 20px;
        border: 1px solid #2d3347;
    }
    
    /* Landscape mode optimization */
    @media (orientation: landscape) and (max-height: 600px) {
        .video-container-wrapper {
            max-height: 50vh;
        }
        
        .episodes-grid {
            max-height: 200px;
        }
        
        .server-buttons-row {
            gap: 4px;
        }
        
        .server-btn {
            padding: 6px 8px;
            font-size: 11px;
        }
        
        .current-info {
            padding: 10px;
        }
        
        .nav-btn, .add-to-list-btn {
            padding: 6px 12px;
            min-height: 36px;
        }
    }
    
    /* Large desktop optimization */
    @media (min-width: 1440px) {
        .player-section {
            max-width: 1400px;
        }
        
        .episodes-grid {
            max-height: 500px;
        }
        
        .server-btn {
            padding: 10px 16px;
            font-size: 14px;
        }
    }
  
    /* Custom scrollbar styling */
    .cast-scroll-container::-webkit-scrollbar {
        height: 0px;
    }
    
    .cast-scroll-container::-webkit-scrollbar-track {
        background: rgba(255,255,255,0.1);
        border-radius: 10px;
    }
    
    .cast-scroll-container::-webkit-scrollbar-thumb {
        background: #4a5f7e;
        border-radius: 10px;
    }
    
    .cast-scroll-container::-webkit-scrollbar-thumb:hover {
        background: #4a5f7e;
    }
    
    /* Hide arrows on mobile by default, show on desktop via media query */
    @media (min-width: 768px) {
        .cast-nav-arrow {
            display: flex !important;
        }
        
        .cast-nav-arrow.left-arrow.hidden,
        .cast-nav-arrow.right-arrow.hidden {
            opacity: 0.3;
            pointer-events: none;
            cursor: default;
        }
    }
    
    @media (max-width: 767px) {
        .cast-nav-arrow {
            display: none !important;
        }
    }
    
    .synopsis-container {
        position: relative;
        cursor: pointer;
        color: #ddd;
        line-height: 1.6;
        font-size: 0.95rem;
        background: #1e2235;
        padding: 20px;
        border-radius: 8px;
        margin-bottom: 20px;
        transition: all 0.3s ease;
        border-left: 3px solid #4685b2;
        max-height: 150px;
        overflow: hidden;
    }
    
    .synopsis-container.expanded {
        max-height: 1000px;
        transition: max-height 0.5s ease-in-out;
    }
    
    .synopsis-container::after {
        content: '';
        position: absolute;
        bottom: 0;
        left: 0;
        width: 100%;
        height: 50px;
        background: linear-gradient(to bottom, transparent, #1e2235);
        pointer-events: none;
        opacity: 1;
        transition: opacity 0.3s ease;
    }
    
    .synopsis-container.expanded::after {
        opacity: 0;
    }
    
    .synopsis-container::before {
        content: 'Click to read more';
        position: absolute;
        bottom: 10px;
        left: 50%;
        transform: translateX(-50%);
        background: #4685b2;
        color: white;
        padding: 4px 12px;
        border-radius: 20px;
        font-size: 0.8rem;
        font-weight: 500;
        opacity: 0;
        transition: opacity 0.3s ease;
        z-index: 2;
        white-space: nowrap;
        pointer-events: none;
    }
    
    .synopsis-container.expanded::before {
        content: 'Click to collapse';
        background: #2a2f45;
    }
    
    .synopsis-container:hover::before {
        opacity: 1;
    }
    
    .synopsis-container.expanded:hover::before {
        opacity: 1;
    }
    
    @media (max-width: 768px) {
        .synopsis-container {
            max-height: 130px;
            padding: 15px;
            font-size: 0.9rem;
        }
        
        .synopsis-container::before {
            font-size: 0.7rem;
            padding: 3px 10px;
        }
    }
    
    @media (max-width: 480px) {
        .synopsis-container {
            max-height: 120px;
        }
    }
    
    .synopsis-container:hover {
        border-left-color: #5c9ed4;
    }
    
    .synopsis-container.expanded {
        cursor: pointer;
    }
</style>

<!-- Player and controls standalone block -->
<div class="player-section" id="standalone-player">
    <!-- Dynamic Video Player -->
    <div class="video-container-wrapper" id="video-player-container-main">
        <div class="video-loading-overlay" id="video-loading-overlay-main">
            <span>▶ Watch Now</span>
        </div>
    </div>

    <!-- Video Control Section -->
    <div class="controls-panel">
        <!-- Current selection info with navigation -->
        <div class="current-info">
            <div class="info-row">
                <div class="info-item"><span>Season:</span> <span class="info-value" id="display-season">2</span></div>
                <div class="info-item"><span>Episode:</span> <span class="info-value" id="display-episode">1</span></div>
                <div class="info-item"><span>Server:</span> <span class="info-value" id="display-server">SUB-HD-01</span></div>
            </div>
            <div class="nav-buttons">
                <button class="nav-btn" id="prev-episode-btn">◀ Prev</button>
                <button class="nav-btn" id="next-episode-btn">Next ▶</button>
                <button class="add-to-list-btn" id="add-to-list-btn">+ Add to List</button>
            </div>
        </div>

        <!-- Server message -->
        <div class="server-message" id="server-message">
           If the current server is down, please try other servers.
        </div>

       <!-- Server Selection: Three categories with HD-01 to HD-05 that work for all seasons -->
<div class="server-category">
    <span class="server-category-label">SUB</span>
    <div class="server-buttons-row" id="server-group-sub">
        <button class="server-btn" data-server="SUB-HD-01">HD-01</button>
        <button class="server-btn" data-server="SUB-HD-02">HD-02</button>
        <button class="server-btn" data-server="SUB-HD-03">HD-03</button>
        <button class="server-btn" data-server="SUB-HD-04">HD-04</button>
        <button class="server-btn" data-server="SUB-HD-05">HD-05</button>
    </div>
</div>

<div class="server-category">
    <span class="server-category-label">DUB</span>
    <div class="server-buttons-row" id="server-group-dub">
        <button class="server-btn" data-server="DUB-HD-01">HD-01</button>
        <button class="server-btn" data-server="DUB-HD-02">HD-02</button>
        <button class="server-btn" data-server="DUB-HD-03">HD-03</button>
        <button class="server-btn" data-server="DUB-HD-04">HD-04</button>
        <button class="server-btn" data-server="DUB-HD-05">HD-05</button>
    </div>
</div>

<div class="server-category">
    <span class="server-category-label">UNCENSORED</span>
    <div class="server-buttons-row" id="server-group-uncensored">
        <button class="server-btn" data-server="UNCENSORED-HD-01">HD-01</button>
        <button class="server-btn" data-server="UNCENSORED-HD-02">HD-02</button>
        <button class="server-btn" data-server="UNCENSORED-HD-03">HD-03</button>
        <button class="server-btn" data-server="UNCENSORED-HD-04">HD-04</button>
        <button class="server-btn" data-server="UNCENSORED-HD-05">HD-05</button>
    </div>
</div>
      
        <!-- Seasons Selection -->
        <div style="margin-top: 16px;">
            <div class="section-title">Watch More Seasons</div>
            <div class="seasons-row" id="seasons-container">
                <button class="season-btn" data-season="1">Season 1</button>
                <button class="season-btn" data-season="2">Season 2</button>
            </div>
        </div>

        <!-- Episodes Selection -->
        <div style="margin-top: 16px;">
            <div class="section-title">Select Episode</div>
            <div class="episodes-grid custom-scrollbar" id="episodes-container"></div>
        </div>

        <div class="helper-note">
            * Select season → episode → server to load video
        </div>
    </div>
</div>

<!-- Include Tailwind and fonts -->
<link href="https://cdn.tailwindcss.com" rel="stylesheet">
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap" rel="stylesheet">

<span><!--more--></span>
<!--[ Thumbnail ]-->
<div style="display: none;">
    <img src="https://i.postimg.cc/KYWqP0Fh/695fd476c525f.jpg" alt="Chained Soldier Season 2" />
</div>
<!--[ Backdrop ]-->
<div class="post-backdrop" style="display: none;">
    <img alt="Slider backdrop" src="https://i.postimg.cc/fWYvgzZV/filters-quality(95)format(webp).jpg">
</div>

<!--[ Synopsis ]-->
<p id="synopsis" class="synopsis-container">
Second season of Mato Seihei no Slave. Yuuki Wakura watches as dueling supernatural forces ravage the Earth. Mato are portals to another dimension, avenues from which dangerous monsters escape. Peaches are resources given to women granting them abilities. Chief of the Seventh Unity of the Anti-Demon Corp, Kyouka Uzen arrives to save Yuuki from a monster. Surprisingly, Yuuki holds the power to increase the Peaches effectiveness. But to save the world, Yuuki must be willing to become Kyouka's servant both on the battlefield and at home.
</p>

<!--[ Extra information ]-->
<div id="extra-info">
    <div class="info-organized">
        <!-- Title -->
        <div><strong>Title:</strong> <span>Chained Soldier Season 2</span></div>

        <!-- Original -->
        <div><strong>Original:</strong> <span>Mato Seihei no Slave</span></div>

        <!-- Japanese/Korean/Chinese/Taiwanese (only for anime/drama) -->
        <div><strong>Japanese:</strong> <span>魔都精兵のスレイブ2</span></div>

        <!-- Synonyms -->
        <div><strong>Synonyms:</strong> <span>Slave of the Magic Capital's Elite Troops, Mabotai</span></div>

        <!-- Aired -->
        <div><strong>Aired:</strong> <span>Jan 08, 2026 to Mar 26, 2026</span></div>

        <!-- Premiered -->
        <div><strong>Premiered:</strong> <span><a href="/search?q=Winter 2026">Winter 2026</a></span></div>

        <!-- Episode -->
        <div><strong>Episode:</strong> <span>12</span></div>

        <!-- Duration -->
        <div><strong>Duration:</strong> <span>23 min</span></div>

        <!-- Broadcast -->
        <div><strong>Broadcast:</strong> <span>Thursdays at 23:00 JST</span></div>

        <!-- Score with Stars (MyAnimeList | IMDb) -->
        <div><strong>Score:</strong> 
            <span class="score-display">
                <!-- MAL Score with Blue Star -->
                <span class="mal-score">
                    <svg class="star-icon mal-star" width="16" height="16" viewBox="0 0 24 24" fill="#3b88c4" style="vertical-align: middle; margin-right: 2px;">
                        <path d="M12 17.27L18.18 21l-1.64-7.03L22 9.24l-7.19-.61L12 2 9.19 8.63 2 9.24l5.46 4.73L5.82 21z"/>
                    </svg>
                    MAL: 8.22
                </span>
                
                <span class="separator" style="margin: 0 5px; color: #aaa;">|</span>
                
                <!-- IMDb Score with Yellow Star -->
                <span class="imdb-score">
                    <svg class="star-icon imdb-star" width="16" height="16" viewBox="0 0 24 24" fill="#f5c518" style="vertical-align: middle; margin-right: 2px;">
                        <path d="M12 17.27L18.18 21l-1.64-7.03L22 9.24l-7.19-.61L12 2 9.19 8.63 2 9.24l5.46 4.73L5.82 21z"/>
                    </svg>
                    IMDb: 7.6
                </span>
            </span>
        </div>

        <!-- Studio -->
        <div><strong>Studio:</strong> 
            <span>
                <a href="/search?q=Passione" title="Passione">Passione</a>
                <a href="/search?q=Hayabusa Film" title="Hayabusa Film">Hayabusa Film</a>
            </span>
        </div>

        <!-- Producer -->
        <div><strong>Producer:</strong> <span>AT-X, Yostar, Pony Canyon, DAX Production, MAGNET</span></div>
    </div>
</div>

<!-- Casts with Smooth Horizontal Scrolling and Navigation Arrows -->
<div style="margin-bottom: 30px; position: relative;">
    <strong style="color: white; display: block; margin-bottom: 15px; font-size: 1.1rem; letter-spacing: 0.5px;">CAST MEMBERS</strong>
    
    <!-- Navigation Arrows (visible only on desktop) -->
    <div class="cast-nav-arrow left-arrow" style="position: absolute; left: -15px; top: 55%; transform: translateY(-50%); z-index: 10; display: none; cursor: pointer; background: rgba(0, 0, 0, 0.3); backdrop-filter: blur(8px); -webkit-backdrop-filter: blur(8px); width: 40px; height: 40px; border-radius: 50%; display: flex; align-items: center; justify-content: center; border: 1px solid rgba(255,255,255,0.2); transition: all 0.3s ease; box-shadow: 0 4px 15px rgba(0,0,0,0.3);" onmouseover="this.style.background='rgba(145,36,58,0.4)'; this.style.borderColor='#91243a'" onmouseout="this.style.background='rgba(0, 0, 0, 0.3)'; this.style.borderColor='rgba(255,255,255,0.2)'">
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
            <path d="M15 18L9 12L15 6" stroke="white" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
        </svg>
    </div>
    
    <div class="cast-nav-arrow right-arrow" style="position: absolute; right: -15px; top: 55%; transform: translateY(-50%); z-index: 10; display: none; cursor: pointer; background: rgba(0, 0, 0, 0.3); backdrop-filter: blur(8px); -webkit-backdrop-filter: blur(8px); width: 40px; height: 40px; border-radius: 50%; display: flex; align-items: center; justify-content: center; border: 1px solid rgba(255,255,255,0.2); transition: all 0.3s ease; box-shadow: 0 4px 15px rgba(0,0,0,0.3);" onmouseover="this.style.background='rgba(145,36,58,0.4)'; this.style.borderColor='#91243a'" onmouseout="this.style.background='rgba(0, 0, 0, 0.3)'; this.style.borderColor='rgba(255,255,255,0.2)'">
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
            <path d="M9 18L15 12L9 6" stroke="white" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
        </svg>
    </div>
    
    <!-- Horizontal Scroll Container -->
    <div class="cast-scroll-container" style="overflow-x: auto; scroll-behavior: smooth; -webkit-overflow-scrolling: touch; scrollbar-width: thin; scrollbar-color: #91243a rgba(255,255,255,0.1); padding: 5px 5px 15px 5px; margin: 0 -5px; position: relative;" onscroll="updateArrowVisibility(this)">
        
        <!-- Cast Grid - Now with flex for horizontal scrolling -->
        <div style="display: flex; flex-direction: row; gap: 15px; min-width: min-content; padding: 0 5px;">
            
            <!-- Cast Member 1: Yuya Hirose / Yuuki Wakura (Japanese) -->
            <a href="/search?q=Yuya+Hirose" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <!-- Perfect Circle Image Container -->
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://cdn.myanimelist.net/r/200x268/images/voiceactors/1/87353.jpg?s=b10bec2e8d57d0ef5a4010c6e2d5d4e7" 
                         alt="Yuya Hirose" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <!-- Cast Info -->
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Yuya Hirose</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Yuuki Wakura (Japanese)</div>
                </div>
            </a>
            
            <!-- Cast Member 2: Gabriel Regojo / Yuuki Wakura (English) -->
            <a href="/search?q=Gabriel+Regojo" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://cdn.myanimelist.net/r/200x268/images/voiceactors/3/43736.jpg?s=7e67d578680a7bc7f4b77efc43c46faf" 
                         alt="Gabriel Regojo" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Gabriel Regojo</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Yuuki Wakura (English)</div>
                </div>
            </a>
            
            <!-- Cast Member 3: Akari Kito / Kyouka Uzen (Japanese) -->
            <a href="/search?q=Akari+Kito" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://cdn.myanimelist.net/r/200x268/images/voiceactors/1/65609.jpg?s=b4901765a5a97c4b51894edbbe23d297" 
                         alt="Akari Kito" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Akari Kito</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Kyouka Uzen (Japanese)</div>
                </div>
            </a>
            
            <!-- Cast Member 4: Anne Yatco / Kyouka Uzen (English) -->
            <a href="/search?q=Anne+Yatco" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://cdn.myanimelist.net/r/200x268/images/voiceactors/2/61137.jpg?s=4d19c852e0284731fcd2e04189c3dfcd" 
                         alt="Anne Yatco" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Anne Yatco</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Kyouka Uzen (English)</div>
                </div>
            </a>
            
            <!-- Cast Member 5: Yume Miyamoto / Himari Azuma (Japanese) -->
            <a href="/search?q=Yume+Miyamoto" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://cdn.myanimelist.net/r/200x268/images/voiceactors/3/58995.jpg?s=e70eb5e0307edff40d4c1c1b24ee2a4f" 
                         alt="Yume Miyamoto" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Yume Miyamoto</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Himari Azuma (Japanese)</div>
                </div>
            </a>
            
            <!-- Cast Member 6: Kristen McGuire / Himari Azuma (English) -->
            <a href="/search?q=Kristen+McGuire" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://myanimelist.net/images/voiceactors/2/47054.jpg" 
                         alt="Kristen McGuire" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Kristen McGuire</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Himari Azuma (English)</div>
                </div>
            </a>
            
            <!-- Cast Member 7: Mari Hino / Shushu Suruga (Japanese) -->
            <a href="/search?q=Mari+Hino" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://cdn.myanimelist.net/r/200x268/images/voiceactors/2/87335.jpg?s=6cb55fd6abbd4e724f04fa7b367c63e3" 
                         alt="Mari Hino" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Mari Hino</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Shushu Suruga (Japanese)</div>
                </div>
            </a>
            
            <!-- Cast Member 8: Juliet Simmons / Shushu Suruga (English) -->
            <a href="/search?q=Juliet+Simmons" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://cdn.myanimelist.net/r/200x268/images/voiceactors/3/46766.jpg?s=bc555ce39134be4e91943d5366d6a370" 
                         alt="Juliet Simmons" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Juliet Simmons</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Shushu Suruga (English)</div>
                </div>
            </a>
            
            <!-- Cast Member 9: Hina Tachibana / Nei Ookawamura (Japanese) -->
            <a href="/search?q=Hina+Tachibana" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://i.postimg.cc/YCch9s9W/latest-cb-20260106204747.webp" 
                         alt="Hina Tachibana" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Hina Tachibana</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Nei Ookawamura (Japanese)</div>
                </div>
            </a>
            
            <!-- Cast Member 10: Monica Rial / Nei Ookawamura (English) -->
            <a href="/search?q=Monica+Rial" style="text-decoration: none; display: flex; align-items: center; gap: 12px; padding: 10px 15px 10px 10px; border: 2px solid rgba(255,255,255,0.1); border-radius: 100px; background: transparent; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); flex-shrink: 0; width: auto;" 
               onmouseover="this.style.backgroundColor='rgba(145,36,58,0.15)'; this.style.borderColor='#91243a'; this.style.transform='translateY(-2px)'" 
               onmouseout="this.style.backgroundColor='transparent'; this.style.borderColor='rgba(255,255,255,0.1)'; this.style.transform='translateY(0)'" 
               onclick="this.style.backgroundColor='#91243a'; this.style.color='white'; this.style.borderColor='#91243a'">
                
                <div style="width: 50px; height: 50px; border-radius: 50%; overflow: hidden; flex-shrink: 0; border: 3px solid rgba(255,255,255,0.2); box-shadow: 0 4px 8px rgba(0,0,0,0.2);">
                    <img src="https://cdn.myanimelist.net/r/200x268/images/voiceactors/2/37923.jpg?s=8b5b2df47e3f83254900976860e89b05" 
                         alt="Monica Rial" 
                         style="width: 100%; height: 100%; object-fit: cover; display: block;">
                </div>
                
                <div style="flex: 1; min-width: 0;">
                    <div style="color: white; font-weight: 600; font-size: 0.95rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Monica Rial</div>
                    <div style="color: #aaa; font-size: 0.8rem; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">Nei Ookawamura (English)</div>
                </div>
            </a>
        </div>
    </div>
    
    <!-- Scroll Instruction (optional) -->
    <div style="text-align: right; margin-top: 8px; color: #777; font-size: 0.75rem; display: flex; align-items: center; justify-content: flex-end; gap: 5px;">
        <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
            <path d="M9 18L15 12L9 6" stroke="#777" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
        </svg>
        <span>Swipe to scroll more</span>
        <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
            <path d="M15 18L9 12L15 6" stroke="#777" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
        </svg>
    </div>
</div>

<script>
    // Function to handle arrow clicks and visibility
    function setupCastScrolling() {
        const container = document.querySelector('.cast-scroll-container');
        const leftArrow = document.querySelector('.left-arrow');
        const rightArrow = document.querySelector('.right-arrow');
        
        if (!container || !leftArrow || !rightArrow) return;
        
        // Scroll amount (adjust as needed)
        const scrollAmount = 300;
        
        // Left arrow click
        leftArrow.addEventListener('click', function() {
            container.scrollBy({
                left: -scrollAmount,
                behavior: 'smooth'
            });
        });
        
        // Right arrow click
        rightArrow.addEventListener('click', function() {
            container.scrollBy({
                left: scrollAmount,
                behavior: 'smooth'
            });
        });
        
        // Update arrow visibility based on scroll position
        function updateArrows() {
            const isAtStart = container.scrollLeft <= 5;
            const isAtEnd = container.scrollLeft + container.clientWidth >= container.scrollWidth - 5;
            
            leftArrow.classList.toggle('hidden', isAtStart);
            rightArrow.classList.toggle('hidden', isAtEnd);
        }
        
        // Initial update
        setTimeout(updateArrows, 100); // Small delay to ensure container dimensions are ready
        
        // Update on scroll
        container.addEventListener('scroll', updateArrows);
        
        // Update on window resize
        window.addEventListener('resize', updateArrows);
    }
    
    // Run when DOM is loaded
    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', setupCastScrolling);
    } else {
        setupCastScrolling();
    }
    
    // Also expose function globally for the onscroll attribute
    window.updateArrowVisibility = function(container) {
        const leftArrow = document.querySelector('.left-arrow');
        const rightArrow = document.querySelector('.right-arrow');
        
        if (!leftArrow || !rightArrow) return;
        
        const isAtStart = container.scrollLeft <= 5;
        const isAtEnd = container.scrollLeft + container.clientWidth >= container.scrollWidth - 5;
        
        leftArrow.classList.toggle('hidden', isAtStart);
        rightArrow.classList.toggle('hidden', isAtEnd);
    };
    
   (function() {
    // Episode titles for Season 01
    const season1Titles = [
        "Birth, Yuuki, Awakening",
        "Curiosity, Shushu, Undress",
        "Encounter, Kyouka, Rampage",
        "Whirlwind, Himari, Roar",
        "Sisters, Yachiho, Ridicule",
        "Blitz, Sahara, Twinkle",
        "United Front, Tenka, Soar",
        "Promise, Nei, Remember",
        "Reunion, Coco, Lick",
        "War, Naon, Recite",
        "Death Match, Aoba, Excite",
        "Homecoming, New, Resolve"
    ];
    
    // Episode titles for Season 02
    const season2Titles = [
        "Commanders' Meeting",
        "Ren's Shadow",
        "A Storm Rolls In",
        "Rampage",
        "The Azuma Banquet",
        "A New Azuma",
        "Late Summer Slave",
        "The Commander of the 2nd Squadron",
        "A Commander's Resolve",
        "Episode 10",
        "Episode 11",
        "Episode 12"
    ];

    // ============================================
    // SEASON 01 - EPISODE LINKS
    // Replace these with your actual Season 1 links
    // ============================================
    const season1SubHD01 = [
        'https://your-server.com/s01e01-sub.m3u8',
        'https://your-server.com/s01e02-sub.m3u8',
        'https://your-server.com/s01e03-sub.m3u8',
        'https://your-server.com/s01e04-sub.m3u8',
        'https://your-server.com/s01e05-sub.m3u8',
        'https://your-server.com/s01e06-sub.m3u8',
        'https://your-server.com/s01e07-sub.m3u8',
        'https://your-server.com/s01e08-sub.m3u8',
        'https://your-server.com/s01e09-sub.m3u8',
        'https://your-server.com/s01e10-sub.m3u8',
        'https://your-server.com/s01e11-sub.m3u8',
        'https://your-server.com/s01e12-sub.m3u8'
    ];
   const season1DubHD01 = [
    'https://your-server.com/s01e01-dub.m3u8',
    'https://your-server.com/s01e02-dub.m3u8',
    'https://your-server.com/s01e03-dub.m3u8',
    'https://your-server.com/s01e04-dub.m3u8',
    'https://your-server.com/s01e05-dub.m3u8',
    'https://your-server.com/s01e06-dub.m3u8',
    'https://your-server.com/s01e07-dub.m3u8',
    'https://your-server.com/s01e08-dub.m3u8',
    'https://your-server.com/s01e09-dub.m3u8',
    'https://your-server.com/s01e10-dub.m3u8',
    'https://your-server.com/s01e11-dub.m3u8',
    'https://your-server.com/s01e12-dub.m3u8'
];
   const season1UncensoredHD01 = [
    'https://your-server.com/s01e01-uncensored.m3u8',
    'https://your-server.com/s01e02-uncensored.m3u8',
    'https://your-server.com/s01e03-uncensored.m3u8',
    'https://your-server.com/s01e04-uncensored.m3u8',
    'https://your-server.com/s01e05-uncensored.m3u8',
    'https://your-server.com/s01e06-uncensored.m3u8',
    'https://your-server.com/s01e07-uncensored.m3u8',
    'https://your-server.com/s01e08-uncensored.m3u8',
    'https://your-server.com/s01e09-uncensored.m3u8',
    'https://your-server.com/s01e10-uncensored.m3u8',
    'https://your-server.com/s01e11-uncensored.m3u8',
    'https://your-server.com/s01e12-uncensored.m3u8'
];

    // ============================================
    // SEASON 02 - EPISODE LINKS (YOUR CURRENT LINKS)
    // ============================================
    const season2SubHD01 = [
        'https://rrr.lab27core.site/po47/c5/h6a90f70b8d237f94866b6cfc2b6349bddedc7dc1328a916ca7342d7529f329e7ee5b899eb0e27ac0c102a43593dab6413f433b153ccb0ab11f97c3d60ebb5bf2/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.hub26link.site/pwjj/c5/h6a90f70b8d237f94866b6cfc2c7f06afdb8423c6639e9e32f874373137a720a9ab58d58cb9be75c7c50ae72297d2e4026207791c2b9b0fe41c8cc89353a146e35d/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.shop21pro.site/prjp/c5/h6a90f70b8d237f94866b6cfc286349bddedc7dc1328a917fa7212a752dfd2db0ee5b899eb0e27ac0c102a43593daab1f7843241c31890fe30097c9d60ebb5bf2/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.shop21pro.site/pxm8/c5/h6a90f70b8d237f94866b6cfc2a6349bddedc7dc1328a917ba7222b7572ba6ba7e105899eb0e27ac0c102a43593daa1183043241c31890fe30097c9d60ebb5bf2/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.lab27core.site/pp36/c5/h6a90f70b8d237f94866b6cfc2e6349bddedc7dc1328a916da7363d7575bc20aef40e899eb0e27ac0c102a43593daa9463e433b153ccb0ab11f97c3d60ebb5bf2/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.dev23app.site/p83e/c5/h6a90f70b8d237f94866b6cfc2b6349bddedc7dc1328a917ea73c3c752ffc2fe8ef00899eb0e27ac0c102a43593dae1466d43331128cb0eb30095888b14a64a/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.hub26link.site/pj67/c5/h6a90f70b8d237f94866b6cfc2c7c06afdb8423c6639e9e32e074316337bb63e7f20ed78cb9be75c7c50ae72297d2e41f3e5a791c2b9b0fe41c8cc89353a146e35d/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.lab27core.site/pvmo/c5/h6a90f70b8d237f94866b6cfc286349bddedc7dc1328a916ea7373d756ea772ebaa01899eb0e27ac0c102a43593daaf1867433b153ccb0ab11f97c3d60ebb5bf2/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.code29wave.site/pklk/c5/h6a90f70b8d237f94866b6cfc256349bddedc7dc1328a916ba76929756fa675afeb00899eb0e27ac0c102a43593dab2196343341b3a9c0feb0784d09d53a146e35d/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        '', '', '' // Episodes 10-12 placeholders
    ];
     
      const season2DubHD01 = [
        'https://rrr.lab27core.site/prjp/c5/h6a90f70b8d237f94866b6cfc2c7e06afdb8423c6639e9e32b8742e3237a720a4e1059c8cb9be75c7c50ae72297d2e407621d79183f9b0fe5138ad49d53a146e35d/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8'
        ];

    // ============================================
    // SEASON 02 - UNCENSORED LINKS (YOUR CURRENT LINKS)
    // ============================================
    const season2UncensoredHD01 = [
        'https://rrr.hub26link.site/pvmo/c5/h6a90f70b8d237f94866b6cfc256349bddedc7dc1328a917ea7302b7520f273a4ad58899eb0e27ac0c102a43593daaf1867433f013ccb0bbe198bcdd60ebb5bf2/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.pro25zone.site/pp36/c5/h6a90f70b8d237f94866b6cfc2c7906afdb8423c6639e9e32ef743e2e37a168aca94cc18cb9be75c7c50ae72297d2e4053b5b79042c960fe70a8ac89d53a146e35d/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.code29wave.site/p83e/c5/h6a90f70b8d237f94866b6cfc2c7e06afdb8423c6639e9e32ee74392a37ff2fedf407988cb9be75c7c50ae72297d2e44d3b087917319d58e04992c78e18fc5cfe4c1a/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.app28base.site/p85e/c5/h6a90f70b8d237f94866b6cfc2c7e06afdb8423c6639e9e32f074316b37a06ba8e34f9b8cb9be75c7c50ae72297d2e44d3d0879152e890fea1284d59d53a146e35d/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.dev23app.site/pe28/c5/h6a90f70b8d237f94866b6cfc2a6349bddedc7dc1328a9178a72b6b756fa673eca001899eb0e27ac0c102a43593dabc473043331128cb0eb30095888b14a64a/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.hub26link.site/p4gw/c5/h6a90f70b8d237f94866b6cfc2c7f06afdb8423c6639e9e32ee742e3d37bd75e8af419d8cb9be75c7c50ae72297d2e4416f1a791c2b9b0fe41c8cc89353a146e35d/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.pro25zone.site/p93z/c5/h6a90f70b8d237f94866b6cfc2b6349bddedc7dc1328a917ca72c2c7569fb2db2ef41899eb0e27ac0c102a43593dae0467243270631cb08a81f8bc3d60ebb5bf2/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.tech20hub.site/p7vq/c5/h6a90f70b8d237f94866b6cfc296349bddedc7dc1328a9178a72e6f752cfd72b4f75b899eb0e27ac0c102a43593daee03794323113d910fe21890c4d60ebb5bf2/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        'https://rrr.hub26link.site/p267/c5/h6a90f70b8d237f94866b6cfc2c7d06afdb8423c6639e9e32eb742d3037fb2feba900968cb9be75c7c50ae72297d2e4473e5a791c2b9b0fe41c8cc89353a146e35d/list,Ktm0Vt9-cJyXbGG_O3gV_5vGK-kpiQ.m3u8',
        '', '', '' // Episodes 10-12 placeholders
    ];

    // ============================================
    // MASTER EPISODE DATABASE
    // All episodes organized by season and type
    // ============================================
    const episodeDatabase = {
        // Season 1 episodes
        '1': {
            'SUB': season1SubHD01,
            'DUB': season1DubHD01, // Add your Season 1 DUB links here
            'UNCENSORED':  season1UncensoredHD01 // Add your Season 1 UNCENSORED links here
        },
        // Season 2 episodes
        '2': {
            'SUB': season2SubHD01,
            'DUB': season2DubHD01,
            'UNCENSORED': season2UncensoredHD01
        }
    };

    // ============================================
    // SERVER MIRRORS (HD-02 through HD-05)
    // For now, they point to the same links as HD-01
    // Replace with actual mirror links when available
    // ============================================
    const serverMirrors = {
        'SUB-HD-01': (season) => episodeDatabase[season]['SUB'],
        'SUB-HD-02': (season) => episodeDatabase[season]['SUB'], // Replace with actual mirror
        'SUB-HD-03': (season) => episodeDatabase[season]['SUB'], // Replace with actual mirror
        'SUB-HD-04': (season) => episodeDatabase[season]['SUB'], // Replace with actual mirror
        'SUB-HD-05': (season) => episodeDatabase[season]['SUB'], // Replace with actual mirror
        
        'DUB-HD-01': (season) => episodeDatabase[season]['DUB'],
        'DUB-HD-02': (season) => episodeDatabase[season]['DUB'], // Replace with actual mirror
        'DUB-HD-03': (season) => episodeDatabase[season]['DUB'], // Replace with actual mirror
        'DUB-HD-04': (season) => episodeDatabase[season]['DUB'], // Replace with actual mirror
        'DUB-HD-05': (season) => episodeDatabase[season]['DUB'], // Replace with actual mirror
        
        'UNCENSORED-HD-01': (season) => episodeDatabase[season]['UNCENSORED'],
        'UNCENSORED-HD-02': (season) => episodeDatabase[season]['UNCENSORED'], // Replace with actual mirror
        'UNCENSORED-HD-03': (season) => episodeDatabase[season]['UNCENSORED'], // Replace with actual mirror
        'UNCENSORED-HD-04': (season) => episodeDatabase[season]['UNCENSORED'], // Replace with actual mirror
        'UNCENSORED-HD-05': (season) => episodeDatabase[season]['UNCENSORED'] // Replace with actual mirror
    };

    // Episode data for both seasons
    const episodeData = {
        '1': season1Titles.map((title, idx) => ({ id: idx+1, title })),
        '2': season2Titles.map((title, idx) => ({ id: idx+1, title }))
    };

    // State
    let currentSeason = '2'; // Default to Season 2
    let currentEpisode = 1;
    let currentServer = 'SUB-HD-01';

    // DOM elements
    const container = document.getElementById('video-player-container-main');
    const overlay = document.getElementById('video-loading-overlay-main');
    const displaySeason = document.getElementById('display-season');
    const displayEpisode = document.getElementById('display-episode');
    const displayServer = document.getElementById('display-server');
    const episodesContainer = document.getElementById('episodes-container');
    const seasonBtns = document.querySelectorAll('.season-btn');
    const serverBtns = document.querySelectorAll('.server-btn');
    const prevBtn = document.getElementById('prev-episode-btn');
    const nextBtn = document.getElementById('next-episode-btn');
    const addToListBtn = document.getElementById('add-to-list-btn');

    function updateInfoDisplay() {
        if (displaySeason) displaySeason.innerText = currentSeason;
        if (displayEpisode) displayEpisode.innerText = currentEpisode;
        if (displayServer) displayServer.innerText = currentServer;
    }

    function clearServerActive() {
        serverBtns.forEach(btn => btn.classList.remove('active-server'));
    }

    function clearSeasonActive() {
        seasonBtns.forEach(btn => btn.classList.remove('active-season'));
    }

    function loadVideo() {
        if (!container) return;
        const episodes = episodeData[currentSeason] || [];
        if (currentEpisode > episodes.length) currentEpisode = 1;

        const episodeIndex = currentEpisode - 1;
        let videoUrl = '';
        
        // Get the URL array for current season and server
        const serverFunc = serverMirrors[currentServer];
        if (serverFunc) {
            const seasonEpisodes = serverFunc(currentSeason);
            if (seasonEpisodes && episodeIndex < seasonEpisodes.length && seasonEpisodes[episodeIndex]) {
                videoUrl = seasonEpisodes[episodeIndex];
            }
        }

        if (!videoUrl) {
            container.innerHTML = '<div class="video-container" style="display: flex; align-items: center; justify-content: center; color: white; background: #000;">No video available for this episode</div>';
            return;
        }

        let embedUrl = videoUrl;
        if (videoUrl.includes('strmup.to')) {
            embedUrl = videoUrl + (videoUrl.includes('?') ? '&' : '?') + 'autoplay=1&controls=1&modestbranding=1&rel=0';
        } else {
            embedUrl = videoUrl + (videoUrl.includes('?') ? '&' : '?') + 'autoplay=1';
        }

        container.innerHTML = '';
        const iframe = document.createElement('iframe');
        iframe.className = 'video-container';
        iframe.src = embedUrl;
        iframe.frameBorder = '0';
        iframe.allow = 'accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture';
        iframe.allowFullscreen = true;
        iframe.title = `S${currentSeason} E${currentEpisode}`;
        container.appendChild(iframe);

        if (overlay) overlay.style.display = 'none';
    }

    function renderEpisodes() {
        const episodes = episodeData[currentSeason] || [];
        let html = '';
        episodes.forEach(ep => {
            const activeClass = (ep.id === currentEpisode) ? 'active' : '';
            const epNumber = ep.id.toString().padStart(2, '0');
            html += `<div class="episode-list-item ${activeClass}" data-episode-id="${ep.id}">EP ${epNumber}: ${ep.title}</div>`;
        });
        episodesContainer.innerHTML = html;

        document.querySelectorAll('.episode-list-item').forEach(el => {
            el.addEventListener('click', function(e) {
                const epId = parseInt(this.dataset.episodeId);
                if (!isNaN(epId)) {
                    currentEpisode = epId;
                    document.querySelectorAll('.episode-list-item').forEach(item => item.classList.remove('active'));
                    this.classList.add('active');
                    updateInfoDisplay();
                    if (currentServer) loadVideo();
                }
            });
        });
    }

    function init() {
        clearSeasonActive();
        seasonBtns.forEach(btn => {
            if (btn.dataset.season === currentSeason) {
                btn.classList.add('active-season');
            }
        });

        clearServerActive();
        serverBtns.forEach(btn => {
            if (btn.dataset.server === currentServer) {
                btn.classList.add('active-server');
            }
        });

        renderEpisodes();
        updateInfoDisplay();
    }

    // Event listeners
    seasonBtns.forEach(btn => {
        btn.addEventListener('click', function() {
            const season = this.dataset.season;
            if (!season) return;
            currentSeason = season;
            currentEpisode = 1;
            clearSeasonActive();
            this.classList.add('active-season');
            renderEpisodes();
            updateInfoDisplay();
            if (currentServer) loadVideo();
        });
    });

    serverBtns.forEach(btn => {
        btn.addEventListener('click', function() {
            const server = this.dataset.server;
            if (!server) return;
            currentServer = server;
            clearServerActive();
            this.classList.add('active-server');
            updateInfoDisplay();
            loadVideo();
        });
    });

    if (prevBtn) {
        prevBtn.addEventListener('click', function() {
            const episodes = episodeData[currentSeason] || [];
            const currentIndex = episodes.findIndex(ep => ep.id === currentEpisode);
            if (currentIndex > 0) {
                currentEpisode = episodes[currentIndex - 1].id;
                renderEpisodes();
                updateInfoDisplay();
                if (currentServer) loadVideo();
            }
        });
    }

    if (nextBtn) {
        nextBtn.addEventListener('click', function() {
            const episodes = episodeData[currentSeason] || [];
            const currentIndex = episodes.findIndex(ep => ep.id === currentEpisode);
            if (currentIndex < episodes.length - 1) {
                currentEpisode = episodes[currentIndex + 1].id;
                renderEpisodes();
                updateInfoDisplay();
                if (currentServer) loadVideo();
            }
        });
    }

    if (addToListBtn) {
        const storageKey = 'quravel_list_status';
        const savedStatus = localStorage.getItem(storageKey);
        if (savedStatus === 'in_list') {
            addToListBtn.innerHTML = '✓ In List';
            addToListBtn.style.background = '#498BBB';
            addToListBtn.style.color = 'white';
            addToListBtn.style.borderColor = '#498BBB';
        }

        addToListBtn.addEventListener('click', function() {
            if (this.innerText.includes('Add')) {
                this.innerHTML = '✓ In List';
                this.style.background = '#498BBB';
                this.style.color = 'white';
                this.style.borderColor = '#498BBB';
                localStorage.setItem(storageKey, 'in_list');
            } else {
                this.innerHTML = '+ Add to List';
                this.style.background = '#141a25';
                this.style.color = '#e5e7eb';
                this.style.borderColor = '#498BBB';
                localStorage.removeItem(storageKey);
            }
        });
    }

    if (overlay) {
        overlay.addEventListener('click', function() {
            if (currentServer) loadVideo();
        });
    }

    // Initialize the player
    init();
})();
    document.addEventListener('DOMContentLoaded', function() {
        const synopsis = document.getElementById('synopsis');
        
        if (synopsis) {
            synopsis.addEventListener('click', function(e) {
                e.stopPropagation();
                this.classList.toggle('expanded');
            });
        }
    });
</script>
