const express = require('express');

const app = express();

const PORT = process.env.PORT || 8000;

app.get('/', (req, res) => {
    return res.send(`
    <!DOCTYPE html>
    <html lang="en">
      <head>
        <meta charset="utf-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <title>Login - Ecommerce</title>
        <link rel="stylesheet" href="login.css" />
        <link
          rel="stylesheet"
          href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.1/css/all.min.css"
          integrity="sha512-DTOQO9RWCH3ppGqcWaEA1BIZOC6xxalwEsw9c2QQeAIftl+Vegovlnee1c9QX4TctnWMn13TZye+giMm8e2LwA=="
          crossorigin="anonymous"
          referrerpolicy="no-referrer"
        />
        <link
          href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css"
          rel="stylesheet"
          integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN"
          crossorigin="anonymous"
        />
       
      </head>
      <body>
      <section class="vh-100" style="background-color: #508bfc;">
      <div class="container py-5 h-100">
        <div class="row d-flex justify-content-center align-items-center h-100">
          <div class="col-12 col-md-8 col-lg-6 col-xl-5">
            <div class="card shadow-2-strong" style="border-radius: 1rem;">
              <div class="card-body p-5 text-center">
                <h3 class="mb-5">Sign in</h3>
                <div class="form-outline mb-4">
                  <input type="email" id="typeEmailX-2" placeholder="Email" class="form-control form-control-lg" />
                </div>
                <div class="form-outline mb-4">
                  <input type="password" id="typePasswordX-2" placeholder="Password" class="form-control form-control-lg" />
                </div>
                <button class="btn btn-primary btn-lg btn-block" type="submit">Login</button>
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>
    
        <script
          src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js"
          integrity="sha384-C6RzsynM9kWDrMNeT87bh95OGNyZPhcTNXj1NW7RuBCsyN/o0jlpcV8Qyq46cDfL"
          crossorigin="anonymous"
        ></script>
      </body>
    </html>
    
    `)
});

app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}...`);
});