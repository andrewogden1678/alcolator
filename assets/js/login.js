// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        username: '',
        password: ''
    },
    methods: {
        /// Login
        login: function () {
            window.OnLogin(this.username, this.password);
        }
    }
});

// Defined here again because the login page is intentionally not compatible with window.js
let close = new Vue({
    el: '#close', // ID for the close button
    methods: {
        winClose: function () {
            window.OnWindowClose();
        }
    }
});