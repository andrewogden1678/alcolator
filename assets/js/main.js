var ComponentRecord = Vue.component('record', {
    data: function() {
        return {

        }
    },
    props: ["record"],
    template: '<div class="flexbox-row--align margin--dataitem dataitem" style="min-height: 73px;"><i class="material-icons list-icon" style="width: 20%; margin-right: 20px; margin-left: 5px">assignment_ind</i><div class="flexbox-column--align"><div class="flexbox-row--alignleft"><h5 class="nomargin" style="text-align: left;">{{record.code}}</h5></div><div class="flexbox-row--alignleft"><h3 class="nomargin" style="text-align: left;">{{record.date}}</h3></div></div></div>'
});

// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        records: [

        ]
    },
    components: {
        'record': ComponentRecord
    },
    methods: {
        /// File methods
        fileMenu: function () {
            var array = window.OnClickFile();
            this.records.push({id: 1, code: array[0], date: array[1]});
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
        },
        // WINDOW stuff
        winClose: function () {
            window.OnWindowClose();
        }
    }
});