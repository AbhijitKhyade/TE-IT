const express = require('express');
const { getAllUsers } = require('../controllers/user.controllers');
//router object
const router = express.Router();

router.get('/users',getAllUsers);

module.exports = router;