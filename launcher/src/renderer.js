// Launcher Renderer Process
const { ipcRenderer } = require('electron');
const { spawn } = require('child_process');
const path = require('path');

// Window controls
document.getElementById('minimize').addEventListener('click', () => {
    require('electron').remote.getCurrentWindow().minimize();
});

document.getElementById('close').addEventListener('click', () => {
    require('electron').remote.getCurrentWindow().close();
});

// Play button
document.getElementById('play-button').addEventListener('click', () => {
    launchGame();
});

// Menu buttons
document.getElementById('story-mode').addEventListener('click', () => {
    launchGame('--mode=story');
});

document.getElementById('multiplayer').addEventListener('click', () => {
    launchGame('--mode=multiplayer');
});

document.getElementById('settings').addEventListener('click', () => {
    // Open settings
    console.log('Opening settings...');
});

document.getElementById('quit').addEventListener('click', () => {
    require('electron').remote.app.quit();
});

function launchGame(args = '') {
    const status = document.getElementById('status');
    status.textContent = 'Launching game...';
    
    // Path to game executable
    const gamePath = path.join(__dirname, '../../bin/BrazilianFootball');
    
    const gameProcess = spawn(gamePath, args.split(' ').filter(Boolean));
    
    gameProcess.on('spawn', () => {
        status.textContent = 'Game running';
    });
    
    gameProcess.on('error', (err) => {
        status.textContent = 'Failed to launch game';
        console.error('Launch error:', err);
    });
    
    gameProcess.on('close', (code) => {
        status.textContent = 'Ready to play';
        console.log(`Game exited with code ${code}`);
    });
}

// Load news feed
function loadNews() {
    const newsFeed = document.getElementById('news-feed');
    
    // Placeholder news items
    const news = [
        { title: 'Welcome to Brazilian Football!', date: '2026-11-05' },
        { title: 'Story Mode Coming Soon', date: '2026-11-04' },
        { title: 'Multiplayer Beta Available', date: '2026-11-03' }
    ];
    
    news.forEach(item => {
        const newsItem = document.createElement('div');
        newsItem.className = 'news-item';
        newsItem.innerHTML = `
            <h3>${item.title}</h3>
            <p>${item.date}</p>
        `;
        newsFeed.appendChild(newsItem);
    });
}

loadNews();
