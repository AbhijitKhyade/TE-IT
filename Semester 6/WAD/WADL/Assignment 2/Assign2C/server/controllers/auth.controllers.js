const User = require("../models/user.model");
const jwt = require('jsonwebtoken');


// Function to generate JWT token
function generateAuthToken(user) {
    // Payload for the JWT token containing user information
    const payload = {
        userId: user._id,
        email: user.email,
    };
    // Generate and sign the JWT token
    const token = jwt.sign(payload, process.env.JWT_SECRET_KEY, { expiresIn: '10h' }); 

    return token;
}

const registerController = async (req, res) => {
    try {
        const {email, password, name} = req.body;
        
        // Check if email is already registered
        const existingUser = await User.findOne({ email });
        if (existingUser) {
            return res.status(400).json({ message: 'Email is already registered.' });
        }

        // Create a new user object
        const newUser = new User({
            name,
            email,
            password
        });

        // Save the user
        await newUser.save();

        // Respond with success message
        res.status(201).json({ success: true, message: 'User registered successfully.', user: newUser });
    } catch (error) {
        console.log(error);
    }
}

const loginController = async (req, res) => {
    try {
        const { email, password } = req.body;

        // Find user by email
        const user = await User.findOne({ email });

        // Check if user exists
        if (!user) {
            return res.status(404).json({ message: 'User not found.' });
        }

        // Check if password matches
        if (password !== user.password) {
            return res.status(401).json({ message: 'Invalid password.' });
        }

        // Password matches, create a JWT token for authentication
        const token = generateAuthToken(user);

        // Respond with success message and token
        res.status(200).json({ success: true, message: 'Login successful.', token });
    } catch (error) {
        console.log(error);
        res.status(500).json({ message: 'Internal server error.' });
    }
}

module.exports = { registerController, loginController };