// Window handlers
let window = new Vue({
    el: '#window', // ID for the close button
    data: {
        moveToggle: false,
        moveX,
        moveY
    },
    methods: {
        winClose: function () {
            window.OnWindowClose();
        },
        navPress: function (evt) {
            this.moveToggle = true;
        },
        navRelease: function (evt) {
            this.moveToggle = false;
        },
        navHold: function (evt) {
            window.OnWindowMove(x, y);
        }
    }
});