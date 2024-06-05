
let form = document.querySelector(".needs-validation");

form.addEventListener("submit", (event) => {
    event.preventDefault();
    console.log("Form submitted");
    if (!form.checkValidity()) {
        console.log("Form is not valid");
    } else {
        console.log("Form is valid");
        // Collect registration data
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

        // Store registration data in localStorage
        let registrationData = JSON.parse(localStorage.getItem('registrationData')) || [];
        registrationData.push(formData);
        localStorage.setItem('registrationData', JSON.stringify(registrationData));

        // Redirect to a new page
        window.location.href = "users.html";
    }

    form.classList.add("was-validated");
},
    false
);