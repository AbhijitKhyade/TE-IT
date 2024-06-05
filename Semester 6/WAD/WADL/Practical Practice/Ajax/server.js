const express = require('express');
const fs = require('fs');
const cors = require('cors');
const app = express();

app.use(express.json());
app.use(cors());

app.get('/', (req, res) => {
    res.send('Heelo');
});

app.post('/register', (req, res) => {
    const { name, email } = req.body;
    // console.log('data: ', req.body);

    const userData = {
        name,
        email,
    }

    fs.readFile('user.json', 'utf8', (err, data) => {
        if (err) {
            console.log('Error: ', err);
            return res.status(500).send('Internal Server Error');
        }
        let users = [];
        if (data) {
            users = JSON.parse(data);
        }

        users.push(userData);

        fs.writeFile('user.json', JSON.stringify(users), err => {
            if (err) {
                console.log(err);
                return res.status(500).send('Internal Server Error');
            }
            res.send('User registerd Successfully');
        });
    });
});

app.get('/users', (req, res) => {
    fs.readFile('user.json', 'utf8', (err, data) => {
        if (err) {
            console.error(err);
            res.status(500).send('Internal Server Error');
            return;
        }

        let users = [];
        if (data) {
            users = JSON.parse(data);
        }
        // console.log(users);
        res.json(users);
    });
});

const port = 8080;

app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});