// Record component
var ComponentRecord = Vue.component('record', {
    props: ["record"],
    template: '<div class="flexbox-row--align margin--dataitem dataitem" style="min-height: 73px;"><i class="material-icons list-icon" style="width: 20%; margin-right: 20px; margin-left: 5px">assignment_ind</i><div class="flexbox-column--align"><div class="flexbox-row--alignleft"><h5 class="nomargin" style="text-align: left;">{{record.subject_code}}</h5></div><div class="flexbox-row--alignleft"><h3 class="nomargin" style="text-align: left;">{{record.created_on}}</h3></div></div></div>'
});

// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        user: {},
        experiment: {},
        records: [ // List of all records

        ],
        selected: {}, // Currently selected record
        isNewStart: true,
        isBacMode: false,
        isViewingSubject: false
    },
    components: {
        'record': ComponentRecord
    },
    methods: {
        /// Data events
        loadSubjects: function () {
            // Get subjects
            var subjects = window.OnLoadSubjects();
            // Display subjects
            for (i = 0; i < subjects.length; i++) {
                this.records.push({id: subjects[i][0], 
                    subject_code: subjects[i][1], 
                    created_on: subjects[i][2].split(" ")[0]});
            }
        },
        loadPrevRecord: function (event, id) {
            // Reset selected
            this.selected = {};
            
            // Get the subject
            var subject = window.OnLoadPrevRecord(id);
            
            // Switch gender
            /*switch(subject[4]) {

            }*/

            this.selected = {id: subject[0], 
                subject_code: subject[1], 
                age: subject[2],
                height: subject[3],
                weight: subject[4],
                gender: subject[5],
                created_on: subject[6].split(" ")[0],
                target_bac: subject[7],
                target_bac_time: subject[8],
                amount_grams: subject[9],
                amount_beverage: subject[10],
                actual_bac: subject[11],
                actual_bac_time: subject[12].split(" ")[1],
                beverage_name: subject[13],
                beverage_concentration: subject[14]};
            
            // Set the viewing modes
            this.isViewingSubject = true;
            this.isNewStart = false;
        },
        /// File methods
        fileMenu: function () {
            
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

vm.loadSubjects();