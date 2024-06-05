const User = require("../models/user.model");

const getAllUsers = async (req, res) => {
    try {
        // Fetch all users from the database
        const users = await User.find({}, { name: 1, email: 1, _id: 0 });

        // If there are no users, return an empty array
        if (!users) {
            return res.status(404).json({ message: 'No users found.' });
        }

        // If users are found, return them
        res.status(200).json(users);
    } catch (error) {
        console.error('Error fetching users:', error);
        res.status(500).json({ message: 'Internal server error.' });
    }
};


module.exports = { getAllUsers };