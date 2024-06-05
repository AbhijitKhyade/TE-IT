const express = require('express');
const { registerController, loginController } = require('../controllers/auth.controllers');

//router object
const router = express.Router();

//REGISTER || METHOD POST
router.post('/register', registerController);

// //LOGIN || METHOD POST
router.post('/login', loginController);




module.exports = router;