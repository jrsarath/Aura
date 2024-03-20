// Global variables
let isAuthenticated = false;
const username = "admin";
const password = "password";
// Routing
document.addEventListener("DOMContentLoaded", () => {
  if (isAuthenticated) {
    document.getElementById("login").classList.remove("active");
    document.getElementById("home").classList.add("active");
  }
});
// Stats fetcher
setInterval(() => {
  fetch("/")
    .then((e) => e.json())
    .then((result) => {
      document.getElementById("temperature").innerHTML = `${
        result.temperature?.toFixed(2) || 0
      }&deg;`;
      document.getElementById("humidity").innerHTML = `${
        result.humidity?.toFixed(2) || 0
      }%`;
      document.getElementById("aqi").innerHTML = result.aqi?.toFixed(2) || 0;
    });
}, 1000);
// Login form
document.getElementById("login-form").addEventListener("submit", (e) => {
  e.preventDefault();
  const username_value = document.getElementById("username").value;
  const password_value = document.getElementById("password").value;

  if (username_value === username && password_value === password) {
    document.getElementById("login").classList.remove("active");
    document.getElementById("home").classList.add("active");
  }
});
// Updater
document.getElementById("updater-btn").addEventListener("click", (e) => {
  document.getElementById("updater-btn").disabled = true;
});
