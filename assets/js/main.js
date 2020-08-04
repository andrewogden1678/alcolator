// Record component
var ComponentRecord = Vue.component('record', {
    props: ["record"],
    template: '<div class="flexbox-row--align margin--dataitem dataitem" style="min-height: 73px;"><i class="material-icons list-icon" style="width: 20%; margin-right: 20px; margin-left: 5px">assignment_ind</i><div class="flexbox-column--align"><div class="flexbox-row--alignleft"><h5 class="nomargin" style="text-align: left;">{{record.subject_code}}</h5></div><div class="flexbox-row--alignleft"><h3 class="nomargin" style="text-align: left;">{{record.created_on[0]}}</h3></div></div></div>'
});

// Experiment component
var ComponentExperiment = Vue.component('experiment', {
    props: ["experiment"],
    template: '<h6 class="selectable dropdown-option">{{experiment.name}}</h6>'
});

// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        records: [ // List of all records

        ],
        experiments: [ // List of all experiments

        ],
        user: {}, // Current session user
        experiment: {}, // Currently loaded experiment
        draft: { // Current in progress subject
            subject_code: "",
            age: "",
            height: "",
            weight: "",
            gender: "",
            created_on: "",
            target_bac: "",
            target_bac_time: "",
            amount_grams: "",
            amount_beverage: "",
            actual_bac: "",
            actual_bac_time: "",
            beverage_name: "",
            beverage_concentration: ""
        }, 
        selected: {
            subject_code: ""
        }, // Currently selected record
        isExperimentLoaded: false,
        isNewStart: true, // Program just started
        isBacMode: false, // Subject is in BAC mode
        isViewingSubject: false, // Subject is being viewed
        isFileMenuOpen: false, // File menu is open
        isSettingsMenuOpen: false, // Settings menu is open
        isEnterSubjectOpen: false, // Menu for entering subject code is open
        isLoadExperimentOpen: false // Menu for loading experiment is open
    },
    components: {
        'record': ComponentRecord,
        'experiment': ComponentExperiment
    },
    methods: {
        /// Data events
        initialLoad: function () {
            // TODO: Get user
            
            // Get experiments
            let exps = window.OnLoadExperiments();
            for (i = 0; i < exps.length; i++) {
                this.experiments.push({id: exps[i][0], 
                    name: exps[i][1]});
            }
            
        },
        loadExp: function () {
            // Display subjects if experiment has been chosen
            if (this.experiment.id != null) {
                this.isExperimentLoaded = true;
                let subjects = window.OnLoadSubjects(this.experiment.id);
                
                // Assign subjects
                for (i = 0; i < subjects.length; i++) {
                    this.records.push({id: subjects[i][0], 
                        subject_code: subjects[i][1], 
                        created_on: subjects[i][2].split(" ")});
                }
                // Hide experiment window
                this.isLoadExperimentOpen = false;
            } 
        },
        saveSubject: function () {

        },
        recordClick: function (event, record) {
            // Reset selected
            this.selected = {};
            // If it is the draft
            if (record.subject_code == this.draft.subject_code) {
                // Set the subject code
                this.selected.subject_code = this.draft.subject_code;
                // Reset screen
                this.isViewingSubject = false;
                // Toggle correct screen if BAC mode
                if (this.draft.created_on != "") {
                    this.isBacMode = true;
                }
            } else {
                // Get the subject
                let subject = window.OnClickRecord(record.id);
                
                // TODO: Switch gender
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
                this.isNewStart = false;
                this.isViewingSubject = true;
                }
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
        /// File menu methods
        fileMenu: function () {
            // If already open
            if (this.isFileMenuOpen === true) {
                // Close and return
                this.isFileMenuOpen = false;
                return;
            }
            // Open the file menu
            this.isFileMenuOpen = true;
        },
        fileMenuHide: function (event) {
            // Get menu & target
            let element = this.$refs.menuFile;
            let target = event.target;
            // Check if the target is the file button
            if (target.id === "fm") {
                // Skip other code
                return;
            }
            // If click outside the menu
            if ((element !== target) && !element.contains(target)) {
                // Close menu
                this.isFileMenuOpen = false;
            }
        },
        fileNewSubject: function () {
            this.isEnterSubjectOpen = true;
        },
        newSubjectClose: function () {
            this.isEnterSubjectOpen = false;
        },
        newSubject: function () {
            // Get current datetime and format
            let date = new Date(Date.now()).toISOString().split("T");
            date[1] = date[1].substr(0, date[1].length - 5);
            // Add new card
            this.records.unshift({id: this.records.length, 
                subject_code: this.draft.subject_code, 
                created_on: date});
            // Add code to selected
            this.selected.subject_code = this.draft.subject_code;
            // Process window changes
            this.isEnterSubjectOpen = false;
            this.isNewStart = false;
            this.isViewingSubject = false;
        },
        fileLoadExp: function () {
            this.isLoadExperimentOpen = true;
        },
        chooseExperiment: function (event, experiment) {
            this.isExperimentLoaded = false; // Mark as not loaded
            this.experiment = {id: experiment.id, name: experiment.name}; // Add to active experiment            
        },
        loadExpClose: function () {
            this.isLoadExperimentOpen = false;
        },
        fileLogOut: function () {
            window.OnLogOut();
        },
        /// Settings methods
        settingsOpen: function () {
            // Open
            this.isSettingsMenuOpen = true;            
        },
        settingsClose: function () {
            // Close
            this.isSettingsMenuOpen = false; 
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
        // WINDOW stuff
        winClose: function () {
            // TODO: ARE YOU SURE WINDOW
            window.OnWindowClose();
        }
    },
    created () {
        // Add the click listener
        document.addEventListener('click', this.fileMenuHide);
    },
    destroyed () {
        // Remove the click listener
        document.removeEventListener('click', this.fileMenuHide);
    }
});