
let button = document.querySelector("#btn");

button.addEventListener("click", (event) => {
    event.preventDefault();


    let isValid = true;

    // Password should be at least 4 characters
    let password = document.getElementById('pass').value;
    if (password.length < 4) {
        isValid = false;
        alert("Password should be at least 4 characters");
    }

    // Email should contain '@'
    let email = document.getElementById('email').value;
    if (!email.includes('@')) {
        isValid = false;
        alert("Please enter a valid email address");
    }

    // Date of Birth should not be more than 2004
    let dob = new Date(document.getElementById('dob').value);
    if (dob.getFullYear() > 2004) {
        isValid = false;
        alert("Date of Birth should not be more than 2004");
    }

    // Pincode should have exactly 6 digits
    let pincode = document.getElementById('pincode').value;
    if (!/^\d{6}$/.test(pincode)) {
        isValid = false;
        alert("Pincode should have exactly 6 digits");
    }
    if (isValid) {
        let formData = {
            name: document.getElementById('name').value,
            email: document.getElementById('email').value,
            password: document.getElementById('pass').value,
            dob: document.getElementById('dob').value,
            gender: document.querySelector('input[name="gender"]:checked').value,
            address: document.getElementById('address').value,
            city: document.getElementById('city').value,
            pincode: document.getElementById('pincode').value,
            state: document.getElementById('state').value,
            hobbies: []
        };

        let hobbyCheckboxes = document.querySelectorAll('input[type="checkbox"]:checked');
        hobbyCheckboxes.forEach((checkbox) => {
            formData.hobbies.push(checkbox.value);
        });

        $.ajax({
            type: 'POST',
            url: 'https://jsonplaceholder.typicode.com/posts',
            data: JSON.stringify(formData),
            contentType: 'application/json',
            success: function (response) {
                window.location.href = 'users.html?data=' + encodeURIComponent(JSON.stringify(response));
            },
            error: function (error) {
                console.log('Error:', error)
            }
        })
    }
}
);