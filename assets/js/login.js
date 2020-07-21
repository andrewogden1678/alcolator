// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        password: "this works"
    },
    methods: {
        login: function () {
            window.OnLogin();
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