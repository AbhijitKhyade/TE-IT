const express = require('express');
const path = require('path');
const fs = require('fs');

// Create an instance of Express
const app = express();

// Define the path to the frontend folder
const frontendPath = path.join(__dirname, 'frontend');

// Serve static files from the frontend folder
app.use(express.static(frontendPath));

// Define your REST API routes
app.get('/', (req, res) => {
    // Read the contents of the index.html file
    const indexPath = path.join(frontendPath, 'index.html');
    fs.readFile(indexPath, 'utf8', (err, data) => {
        if (err) {
            res.status(500).send('Error reading index.html file');
            return;
        }
        res.send(data);
    });
});



// Define the port
const PORT = process.env.PORT || 8080;

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}...`);
});
