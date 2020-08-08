// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        username: "",
        password: "",
        incorrectLogin: false
    },
    methods: {
        /// Login
        login: function () {
            // Check credentials
            if (username == "" || password == "") return; // Don't register if not all filled in
            let isCorrect = window.OnLogin(this.username, this.password);
            if (!isCorrect) this.incorrectLogin = true;
        }
    }
});

// Window methods
let close = new Vue({
    el: '#close', // ID for the close button
    methods: {
        winClose: function () {
            window.OnWindowClose();
        }
    }
});