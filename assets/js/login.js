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

// Window methods
let close = new Vue({
    el: '#close', // ID for the close button
    methods: {
        winClose: function () {
            window.OnWindowClose();
        }
    }
});