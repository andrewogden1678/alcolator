// Window handlers
let win = new Vue({
    el: '#win', // ID for the close button
    data: {

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