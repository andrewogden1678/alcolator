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
        fileOpenExp: function () {
            window.OnExperimentOpen();
        },
        fileNewSubject: function () {
            window.OnAddNewSubject();
        },
        fileLogOut: function () {
            window.OnLogOut();
        },
        /// Settings methods
        settingsOpen: function () {
            window.OnClickSettings();
            // make visible css
        },
        settingsBeverageAdd: function () {
            window.OnAddNewBeverage();
        },
        settingsBeverageEdit: function () {
            window.OnEditBeverage();
        },
        /// Sorting methods
        sortClick: function() {
            window.OnClickSort();
        },
        searchSubmit: function () {
            window.OnSearchSubmit();
        },
        /// Record methods
        recordClick: function () {
            window.OnClickRecord();
        },
        calculateClick: function () {
            window.OnClickCalculate();
        },
        administeredClick: function () {
            window.OnClickAdministered();
        },
        bacRecord: function () {
            window.OnClickRecordBAC();
        },
        reportDownload: function () {
            window.OnClickDownloadReport();
        }
    }
});