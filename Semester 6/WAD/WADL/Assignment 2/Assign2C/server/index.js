const express = require('express');
const dotenv = require('dotenv');
const cors = require('cors');

const mongoDB = require('./config/db');
const authRoutes = require('./routes/auth.routes');
const userRoutes = require('./routes/user.routes');

//config dotenv
dotenv.config();

//database config
mongoDB();

//rest object
const app = express();

//middleware
app.use(express.json());
app.use(cors());

//routes
app.use("/auth", authRoutes);
app.use("/user", userRoutes);


//rest api
app.get('/', (req, res) => {
    res.send('<h1>Welcome to the Ecommerce Website using MERN.</h1>');
});

//PORT
const PORT = process.env.PORT || 8080;

//run listen
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}...`);
});