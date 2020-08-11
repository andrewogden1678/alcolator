// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        username: "", // Username
        password: "", // Password
        incorrectLogin: false // Login validation
    },
    methods: {
        /// Login
        login: function () {
            // Check credentials
            if (username == "" || password == "") return; // Don't register if not all filled in

            // Login and validate
            let isCorrect = window.OnLogin(this.username, this.password);

            // If not correct
            if (!isCorrect) this.incorrectLogin = true;
        }
    }
});

// Window close
let close = new Vue({
    el: '#close', // ID for the close button
    methods: {
        // Close the window
        winClose: function () {
            window.OnWindowClose();
        }
    }
});