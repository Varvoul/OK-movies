# 🔌 How to Add Independent Mirror Links for HD-01 to HD-05

## Complete Guide for Adding Multiple Server Mirrors

---

## 📋 Table of Contents
1. [Overview](#overview)
2. [Understanding the Current Setup](#understanding-the-current-setup)
3. [Method 1: Complete Separate Arrays](#method-1-complete-separate-arrays)
4. [Method 2: Using String Replacement](#method-2-using-string-replacement)
5. [Method 3: Mixed Approach](#method-3-mixed-approach)
6. [Complete Working Example](#complete-working-example)
7. [Quick Reference](#quick-reference)
8. [Troubleshooting](#troubleshooting)

---

## Overview

Currently, all HD-01 to HD-05 buttons point to the same links. To make them **independent mirrors**, you need to create separate arrays for each HD number and update the `serverMirrors` function.

This way, if HD-01 fails, users can switch to HD-02, HD-03, etc. for alternative servers.

---

## Understanding the Current Setup

Your current `serverMirrors` looks like this:
```javascript
const serverMirrors = {
    'SUB-HD-01': (season) => episodeDatabase[season]['SUB'],
    'SUB-HD-02': (season) => episodeDatabase[season]['SUB'], // Same as HD-01
    'SUB-HD-03': (season) => episodeDatabase[season]['SUB'], // Same as HD-01
    // ...
};
```

To make them independent, you need to create separate arrays and update the mapping.

---

## Method 1: Complete Separate Arrays

Create completely independent arrays for each HD number.

### Step 1: Create Separate Arrays for Each HD Number

```javascript
// ============================================
// SEASON 02 - SUB EPISODES - INDEPENDENT MIRRORS
// ============================================

// Main server (HD-01)
const season2SubHD01 = [
    'https://main-server.com/s02e01-sub.m3u8',
    'https://main-server.com/s02e02-sub.m3u8',
    // ... up to episode 12
];

// Mirror 1 (HD-02) - Different domain
const season2SubHD02 = [
    'https://mirror1-server.com/s02e01-sub.m3u8',
    'https://mirror1-server.com/s02e02-sub.m3u8',
    // ... up to episode 12
];

// Mirror 2 (HD-03) - Different domain
const season2SubHD03 = [
    'https://mirror2-server.com/s02e01-sub.m3u8',
    'https://mirror2-server.com/s02e02-sub.m3u8',
    // ... up to episode 12
];

// Mirror 3 (HD-04) - Different domain
const season2SubHD04 = [
    'https://mirror3-server.com/s02e01-sub.m3u8',
    'https://mirror3-server.com/s02e02-sub.m3u8',
    // ... up to episode 12
];

// Mirror 4 (HD-05) - Different domain
const season2SubHD05 = [
    'https://mirror4-server.com/s02e01-sub.m3u8',
    'https://mirror4-server.com/s02e02-sub.m3u8',
    // ... up to episode 12
];
```

### Step 2: Update Server Mirrors Function

```javascript
const serverMirrors = {
    // SUB servers with independent mirrors
    'SUB-HD-01': (season) => {
        if (season === '1') return season1SubHD01;
        if (season === '2') return season2SubHD01;
        if (season === '3') return season3SubHD01;
    },
    'SUB-HD-02': (season) => {
        if (season === '1') return season1SubHD02;
        if (season === '2') return season2SubHD02;
        if (season === '3') return season3SubHD02;
    },
    'SUB-HD-03': (season) => {
        if (season === '1') return season1SubHD03;
        if (season === '2') return season2SubHD03;
        if (season === '3') return season3SubHD03;
    },
    'SUB-HD-04': (season) => {
        if (season === '1') return season1SubHD04;
        if (season === '2') return season2SubHD04;
        if (season === '3') return season3SubHD04;
    },
    'SUB-HD-05': (season) => {
        if (season === '1') return season1SubHD05;
        if (season === '2') return season2SubHD05;
        if (season === '3') return season3SubHD05;
    },
    
    // Repeat for DUB and UNCENSORED...
};
```

---

## Method 2: Using String Replacement

If your mirror links follow a pattern (like different domains but same path), you can generate them automatically.

### Step 1: Create Base Array
```javascript
// Base array for Season 2 SUB
const season2SubHD01 = [
    'https://server1.com/path/ep01.m3u8',
    'https://server1.com/path/ep02.m3u8',
    'https://server1.com/path/ep03.m3u8',
    // ... up to episode 12
];
```

### Step 2: Generate Mirrors Using String Replacement
```javascript
// Generate HD-02 by replacing domain
const season2SubHD02 = season2SubHD01.map(url => 
    url.replace('server1.com', 'server2.com')
);

// Generate HD-03 by replacing domain
const season2SubHD03 = season2SubHD01.map(url => 
    url.replace('server1.com', 'server3.com')
);

// Generate HD-04 by replacing domain
const season2SubHD04 = season2SubHD01.map(url => 
    url.replace('server1.com', 'server4.com')
);

// Generate HD-05 by replacing domain
const season2SubHD05 = season2SubHD01.map(url => 
    url.replace('server1.com', 'server5.com')
);
```

### Step 3: Handle Different URL Patterns
```javascript
// If URLs have different patterns, use more complex replacement
const season2SubHD02 = season2SubHD01.map(url => {
    if (url.includes('lab27core.site')) {
        return url.replace('lab27core.site', 'mirror1.site');
    }
    if (url.includes('hub26link.site')) {
        return url.replace('hub26link.site', 'mirror1.site');
    }
    return url; // fallback
});
```

---

## Method 3: Mixed Approach

Combine both methods - use string replacement for some mirrors and manual arrays for others.

```javascript
// ============================================
// SEASON 2 - SUB EPISODES WITH MIXED MIRRORS
// ============================================

// Main server (HD-01) - Your original links
const season2SubHD01 = [
    'https://rrr.lab27core.site/po47/c5/.../list,Ktm0Vt9...',
    'https://rrr.hub26link.site/pwjj/c5/.../list,Ktm0Vt9...',
    // ... all 12 episodes
];

// HD-02 - Generated from HD-01 with domain replacement
const season2SubHD02 = season2SubHD01.map(url => 
    url.replace('lab27core.site', 'mirror1.site')
       .replace('hub26link.site', 'mirror1.site')
       .replace('shop21pro.site', 'mirror1.site')
);

// HD-03 - Generated from HD-01 with different domain
const season2SubHD03 = season2SubHD01.map(url => 
    url.replace('lab27core.site', 'mirror2.site')
       .replace('hub26link.site', 'mirror2.site')
       .replace('shop21pro.site', 'mirror2.site')
);

// HD-04 - Manual entries if pattern is different
const season2SubHD04 = [
    'https://custom-server.com/ep01.m3u8',
    'https://custom-server.com/ep02.m3u8',
    // ... manually add all 12
];

// HD-05 - Another manual mirror
const season2SubHD05 = [
    'https://another-server.com/ep01.m3u8',
    'https://another-server.com/ep02.m3u8',
    // ... manually add all 12
];
```

---

## Complete Working Example

Here's a complete example with independent mirrors for all servers:

```javascript
(function() {
    // Episode titles (your existing code)
    const season1Titles = [ /* ... */ ];
    const season2Titles = [ /* ... */ ];

    // ============================================
    // SEASON 1 - SUB EPISODES WITH INDEPENDENT MIRRORS
    // ============================================
    const season1SubHD01 = [
        'https://main-server.com/s01e01-sub.m3u8',
        'https://main-server.com/s01e02-sub.m3u8',
        'https://main-server.com/s01e03-sub.m3u8',
        'https://main-server.com/s01e04-sub.m3u8',
        'https://main-server.com/s01e05-sub.m3u8',
        'https://main-server.com/s01e06-sub.m3u8',
        'https://main-server.com/s01e07-sub.m3u8',
        'https://main-server.com/s01e08-sub.m3u8',
        'https://main-server.com/s01e09-sub.m3u8',
        'https://main-server.com/s01e10-sub.m3u8',
        'https://main-server.com/s01e11-sub.m3u8',
        'https://main-server.com/s01e12-sub.m3u8'
    ];

    const season1SubHD02 = [
        'https://mirror1.com/s01e01-sub.m3u8',
        'https://mirror1.com/s01e02-sub.m3u8',
        'https://mirror1.com/s01e03-sub.m3u8',
        'https://mirror1.com/s01e04-sub.m3u8',
        'https://mirror1.com/s01e05-sub.m3u8',
        'https://mirror1.com/s01e06-sub.m3u8',
        'https://mirror1.com/s01e07-sub.m3u8',
        'https://mirror1.com/s01e08-sub.m3u8',
        'https://mirror1.com/s01e09-sub.m3u8',
        'https://mirror1.com/s01e10-sub.m3u8',
        'https://mirror1.com/s01e11-sub.m3u8',
        'https://mirror1.com/s01e12-sub.m3u8'
    ];

    const season1SubHD03 = [
        'https://mirror2.com/s01e01-sub.m3u8',
        'https://mirror2.com/s01e02-sub.m3u8',
        // ... and so on
    ];

    // Continue for HD-04 and HD-05...

    // ============================================
    // SEASON 2 - SUB EPISODES (YOUR ORIGINAL LINKS WITH MIRRORS)
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

    // Generate HD-02 mirror by replacing domains
    const season2SubHD02 = season2SubHD01.map(url => {
        if (!url) return '';
        return url.replace('lab27core.site', 'mirror1.lab27core.site')
                  .replace('hub26link.site', 'mirror1.hub26link.site')
                  .replace('shop21pro.site', 'mirror1.shop21pro.site')
                  .replace('dev23app.site', 'mirror1.dev23app.site')
                  .replace('code29wave.site', 'mirror1.code29wave.site');
    });

    // Generate HD-03 mirror with different pattern
    const season2SubHD03 = season2SubHD01.map(url => {
        if (!url) return '';
        return url.replace('rrr.', 'cdn1.'); // Change domain pattern
    });

    // HD-04 manual mirror (if you have specific links)
    const season2SubHD04 = [
        'https://custom-server.com/s02e01.m3u8',
        'https://custom-server.com/s02e02.m3u8',
        // ... you would need all 12 links here
        '', '', '', '', '', '', '', '', '' // Placeholders if missing
    ];

    // HD-05 manual mirror
    const season2SubHD05 = [
        'https://another-server.com/s02e01.m3u8',
        'https://another-server.com/s02e02.m3u8',
        // ... you would need all 12 links here
        '', '', '', '', '', '', '', '', '' // Placeholders if missing
    ];

    // Repeat for DUB and UNCENSORED...
    const season2DubHD01 = [ /* your DUB links */ ];
    const season2DubHD02 = season2DubHD01.map(url => url.replace('domain1', 'domain2'));
    const season2DubHD03 = season2DubHD01.map(url => url.replace('domain1', 'domain3'));
    // ... etc

    const season2UncensoredHD01 = [ /* your UNCENSORED links */ ];
    const season2UncensoredHD02 = season2UncensoredHD01.map(url => url.replace('domain1', 'domain2'));
    const season2UncensoredHD03 = season2UncensoredHD01.map(url => url.replace('domain1', 'domain3'));
    // ... etc

    // ============================================
    // SERVER MIRRORS WITH INDEPENDENT ARRAYS
    // ============================================
    const serverMirrors = {
        // SUB servers with independent mirrors
        'SUB-HD-01': (season) => {
            if (season === '1') return season1SubHD01;
            if (season === '2') return season2SubHD01;
            return [];
        },
        'SUB-HD-02': (season) => {
            if (season === '1') return season1SubHD02;
            if (season === '2') return season2SubHD02;
            return [];
        },
        'SUB-HD-03': (season) => {
            if (season === '1') return season1SubHD03;
            if (season === '2') return season2SubHD03;
            return [];
        },
        'SUB-HD-04': (season) => {
            if (season === '1') return season1SubHD04;
            if (season === '2') return season2SubHD04;
            return [];
        },
        'SUB-HD-05': (season) => {
            if (season === '1') return season1SubHD05;
            if (season === '2') return season2SubHD05;
            return [];
        },
        
        // DUB servers
        'DUB-HD-01': (season) => {
            if (season === '1') return season1DubHD01;
            if (season === '2') return season2DubHD01;
            return [];
        },
        'DUB-HD-02': (season) => {
            if (season === '1') return season1DubHD02;
            if (season === '2') return season2DubHD02;
            return [];
        },
        // ... continue for DUB-HD-03, HD-04, HD-05
        
        // UNCENSORED servers
        'UNCENSORED-HD-01': (season) => {
            if (season === '1') return season1UncensoredHD01;
            if (season === '2') return season2UncensoredHD01;
            return [];
        },
        'UNCENSORED-HD-02': (season) => {
            if (season === '1') return season1UncensoredHD02;
            if (season === '2') return season2UncensoredHD02;
            return [];
        },
        // ... continue for UNCENSORED-HD-03, HD-04, HD-05
    };

    // Rest of your code remains the same...
    // episodeDatabase, episodeData, loadVideo(), etc.
})();
```

---

## Quick Reference

### For Each Season, You Need:

| Server Type | HD-01 | HD-02 | HD-03 | HD-04 | HD-05 |
|-------------|-------|-------|-------|-------|-------|
| **SUB** | `seasonXSubHD01` | `seasonXSubHD02` | `seasonXSubHD03` | `seasonXSubHD04` | `seasonXSubHD05` |
| **DUB** | `seasonXDubHD01` | `seasonXDubHD02` | `seasonXDubHD03` | `seasonXDubHD04` | `seasonXDubHD05` |
| **UNCENSORED** | `seasonXUncensoredHD01` | `seasonXUncensoredHD02` | `seasonXUncensoredHD03` | `seasonXUncensoredHD04` | `seasonXUncensoredHD05` |

### Template for Adding Mirrors:

```javascript
// Base array (HD-01)
const seasonXSubHD01 = [ /* 12 links */ ];

// Generated mirror (HD-02)
const seasonXSubHD02 = seasonXSubHD01.map(url => {
    if (!url) return '';
    return url.replace('original-domain.com', 'mirror-domain.com');
});

// Manual mirror (HD-03)
const seasonXSubHD03 = [
    'https://manual-server.com/ep01.m3u8',
    'https://manual-server.com/ep02.m3u8',
    // ... manually add all 12
];

// Then update serverMirrors for each HD number
```

---

## Troubleshooting

### Problem: Videos don't play on HD-02
**Solution:** 
- Check that `season2SubHD02` array has 12 items
- Verify the URLs are correct and accessible
- Check browser console for errors

### Problem: HD-02 shows same videos as HD-01
**Solution:**
- You're still using the same array reference
- Make sure you created separate arrays, not just copied the reference

❌ **Wrong:**
```javascript
const season2SubHD02 = season2SubHD01; // Both point to same array!
```

✅ **Correct:**
```javascript
const season2SubHD02 = [...season2SubHD01]; // Creates a new array
// OR
const season2SubHD02 = season2SubHD01.map(url => url.replace(...)); // Creates new array
```

### Problem: Some episodes missing on HD-02
**Solution:**
- When using `.map()`, empty strings remain empty
- Make sure your replacement logic handles empty strings
- Check that all 12 positions have values (even if empty)

### Problem: Too many arrays to manage
**Solution:** Use string replacement for most mirrors and only manually create arrays for HD-02 and HD-03 if needed.

---

## Summary

To make HD-01 through HD-05 independent:

1. **Create separate arrays** for each HD number (HD-01, HD-02, HD-03, HD-04, HD-05)
2. **Use string replacement** to generate mirrors from HD-01 if domains follow patterns
3. **Manually create arrays** for mirrors with different structures
4. **Update `serverMirrors`** to return the correct array based on season and HD number
5. **Ensure all arrays have 12 items** (use empty strings as placeholders)

This gives users **5 independent server options** for each category (SUB, DUB, UNCENSORED), so if one server fails, they can switch to another!

---

*Need help generating mirror links? Share your URL patterns and I'll help create the replacement logic!*
