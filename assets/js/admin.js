// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        
    },
    methods: {
        /// File methods
        fileMenu: function () {
            window.OnClickFile();
            // make visible css
        },
        fileAddUser: function () {
            window.OnClickNewUser();
        },
        fileLogOut: function () {
            window.OnLogOut();
        },
        fileNewExp: function () {

        },
        /// Settings methods
        settingsOpen: function () {
            window.OnClickSettings();
            // make visible css
        },
        /// User methods
        /// Settings methods
        saveClick: function () {
            window.OnClickSaveUser();
            // make visible css
        },
        /// Settings methods
        cancelClick: function () {
            window.OnClickCancel();
            // make visible css
        }
    }
});