// Record component
var ComponentRecord = Vue.component('record', {
    props: ["record"],
    template: '<div class="flexbox-row--align margin--dataitem dataitem" style="min-height: 73px;"><i class="material-icons list-icon" style="width: 20%; margin-right: 20px; margin-left: 5px">assignment_ind</i><div class="flexbox-column--align"><div class="flexbox-row--alignleft"><h5 class="nomargin" style="text-align: left;">{{record.subject_code}}</h5></div><div class="flexbox-row--alignleft"><h3 class="nomargin" style="text-align: left;">{{record.created_on[0]}}</h3></div></div></div>'
});

// Dropdown component
var ComponentDropdown = Vue.component('dropdown', {
    props: ["obj"],
    template: '<h6 class="selectable dropdown-option">{{obj.name}}</h6>'
});

// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        records: [ // List of all records

        ],
        experiments: [ // List of all experiments

        ],
        beverages : [

        ],
        // For dropdown component
        gender_male: {
            name: "Male",
            raw: true
        },
        // For dropdown component
        gender_female: {
            name: "Female",
            raw: false
        },
        user: { // Current user in session
            id: 1,
            firstName: "",
            lastName: "",
            accessLevel: "",
        }, 
        experiment: {}, // Currently loaded experiment
        settingsBeverage: {
            id: null,
            newName: "",
            newConc: "",
            name: "",
            concentration: ""
        },
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
        isCalculateClicked: false,
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
        'dropdown': ComponentDropdown
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

            // Get beverages
            this.loadBeverages();
        },
        loadBeverages: function () {
            // Get beverages
            let bevs = window.OnLoadBeverages();
            for (i = 0; i < bevs.length; i++) {
                this.beverages.push({id: bevs[i][0],
                name: bevs[i][1],
                concentration: bevs[i][2]});
            }
        },
        loadSubjects: function () {
            // Reset records
            this.records = [];
            let subjects = window.OnLoadSubjects(this.experiment.id);
                
            // Assign subjects
            for (i = 0; i < subjects.length; i++) {
                this.records.push({id: subjects[i][0], 
                    subject_code: subjects[i][1], 
                    created_on: subjects[i][2].split(" ")});
            }
        },
        loadExp: function () {
            // TODO: VALIDATE
            // Display subjects if experiment has been chosen
            if (this.experiment.id != null) {
                this.isExperimentLoaded = true;
                this.loadSubjects();
                // Hide experiment window
                this.isLoadExperimentOpen = false;
            }

            // Reset selected
            this.resetSelected();
        },
        recordClick: function (event, record) {
            // Reset selected
            this.resetSelected();
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
                
                // Cut off seconds
                let splitTime = subject[12].split(" ")[1].split(":");
                splitTime = splitTime[0] + ":" + splitTime[1];

                // Set selected
                this.selected = {id: subject[0], 
                    subject_code: subject[1], 
                    age: subject[2],
                    height: parseInt(subject[3]),
                    weight: parseFloat(subject[4]).toFixed(1),
                    gender: Boolean(subject[5]) == true ? "Male" : "Female",
                    created_on: subject[6].split(" ")[0],
                    target_bac: parseFloat(subject[7]).toFixed(3),
                    target_bac_time: subject[8],
                    amount_grams: parseFloat(subject[9]).toFixed(1),
                    amount_beverage: parseFloat(subject[10]).toFixed(1),
                    actual_bac: parseFloat(subject[11]).toFixed(3),
                    actual_bac_time: splitTime,
                    beverage_name: subject[13],
                    beverage_concentration: parseFloat(subject[14]).toFixed(3)};
                
                // Set the viewing modes
                this.isNewStart = false;
                this.isBacMode = false;
                this.isViewingSubject = true;
            }
        },
        saveSubject: function () {
            // Define return array
            let returnArray = [];

            // Push items
            returnArray.push(this.draft.subject_code);
            returnArray.push(this.user.id);
            returnArray.push(this.experiment.id);
            returnArray.push(this.draft.age);
            returnArray.push(this.draft.gender);
            returnArray.push(this.draft.height);
            returnArray.push(this.draft.weight);
            returnArray.push(this.draft.created_on);
            // Get beverage
            for (i = 0; i < this.beverages.length; i++) {
                if (this.beverages[i].name == this.draft.beverage_name) {
                    returnArray.push(this.beverages[i].id);
                }
            }
            returnArray.push(this.draft.target_bac);
            returnArray.push(this.draft.target_bac_time);
            returnArray.push(this.draft.amount_grams);
            returnArray.push(this.draft.amount_beverage);
            returnArray.push(this.draft.actual_bac);
            returnArray.push(this.draft.actual_bac_time);

            // Send to database
            window.OnAddNewSubject(returnArray);
        },
        resetSelected: function () {
            // Reset selected
            this.selected = {
                subject_code: ""
            };
        },
        cancelSubject: function () {
            // TODO: ARE YOU SURE GATES
            // Reset draft
            this.draft = {
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
            };

            // Reset selected
            this.resetSelected();

            // Remove the draft sidebar record
            this.records.shift();

            // Reset screen
            this.isNewStart = true;
            this.isCalculateClicked = false;
            
        },
        calculateClick: function () {
            // TODO: VALIDATE
            this.draft.amount_grams = this.calculateConsumption();
            this.draft.amount_beverage = this.calculateBeverage();
            // Show administer button
            this.isCalculateClicked = true;
        },
        administeredClick: function () {        
            // TODO: VALIDATE   
            // Set created on time
            this.draft.created_on = this.getDateNow();

            // Reset calculated check
            this.isCalculateClicked = false;
            // Change screen
            this.isBacMode = true;
        },
        bacRecord: function () {
            // TODO: VALIDATE
            // Get current date
            let date = this.getDateNow();
            // Set actual BAC datetime
            this.draft.actual_bac_time = date;

            // Save the subject
            this.saveSubject();

            // Set selected to the draft
            this.selected = Object.assign({}, this.draft);

            // Cut off seconds
            let splitTime = date.split(" ")[1].split(":");
            this.selected.actual_bac_time = splitTime[0] + ":" + splitTime[1];

            // Reset draft
            this.draft = {
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
            };

            // Set screens
            this.isBacMode = false;
            this.isViewingSubject = true;

            // Reload experiment
            this.loadSubjects();
        },
        reportDownload: function () {
            window.OnClickDownloadReport();
        },
        setGender: function (event, gender) {
            this.draft.gender = gender;
        },
        getDateNow: function () {
            // Get date
            let date = new Date(Date.now());

            // Locales
            let localDate = date.toLocaleDateString();
            let localTime = date.toLocaleTimeString();

            // Format date string for ISO
            localDate = localDate.split("/").reverse().join("-");

            // Connect them together again
            return localDate + " " + localTime;
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
            // TODO: VALIDATE
            // Get current datetime and format
            let date = this.getDateNow().split(" ");
            // Add new card
            this.records.unshift({
                id: this.records.length, 
                subject_code: this.draft.subject_code,
                created_on: date
            });
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
            // Reset values
            this.settingsBeverage = {
                id: null,
                newName: "",
                newConc: "",
                name: "",
                concentration: ""
            };
            // Close menu
            this.isSettingsMenuOpen = false; 
        },
        settingsSave: function () {
            // TODO: VALIDATE
            // Define return array and push values
            let returnArray = [];
            // Return ID if edited and -1 if not
            returnArray.push(this.settingsBeverage.id);
            returnArray.push(this.settingsBeverage.newName);
            returnArray.push(this.settingsBeverage.newConc);
            returnArray.push(this.settingsBeverage.name);
            returnArray.push(parseInt(this.settingsBeverage.concentration) / 100);
            if (this.settingsBeverage.id != null || this.settingsBeverage.concentration != "") {
                returnArray.push(true); // Send true if edited
            } else {
                returnArray.push(false); // Send false if not
            }
            if (this.settingsBeverage.newName != "" || this.settingsBeverage.newConc != "" ) {
                returnArray.push(true); // Send true if new added
            } else {
                returnArray.push(false); // Send false if not
            }
            
            // Push to database
            window.OnAddNewBeverage(returnArray);

            // Reset values
            this.settingsBeverage = {
                id: null,
                newName: "",
                newConc: "",
                name: "",
                concentration: ""
            };

            // Reload beverages
            this.beverages = [];
            this.loadBeverages();
        },
        chooseBeverage: function (event, beverage) {
            // Add to values
            this.settingsBeverage.id = beverage.id;
            this.settingsBeverage.name = beverage.name;
            this.settingsBeverage.concentration = parseFloat(beverage.concentration) * 100;
        },
        chooseBeverageSubject: function (event, beverage) {
            // Add to values
            this.draft.beverage_name = beverage.name;
            this.draft.beverage_concentration = beverage.concentration;
        },
        // CALCULATION METHOD
        calculateConsumption: function () {
            let bac = parseFloat(this.draft.target_bac); // Blood alcohol concentration
            let w = parseFloat(this.draft.weight); // Body weight (kg)
            let h = parseFloat(this.draft.height) / 100; // Height (m)
            let a = parseInt(this.draft.age); // Age (years)
            let gender = Boolean(this.draft.gender == "Male" ? true : false); // Gender (male/female)
            let elimRate = 10; // Alcohol elimination rate (g/h)
            let time = parseFloat(this.draft.target_bac_time); // Time at which to reach target BAC
            let r; // Widmark factor (average)

            // Total body water (TBW) formulae
            let rWidmark;
            let rWatson;
            let rForrest;
            let rSeidl;
            let rUlrich;

            // Calculate R factor
            if (gender) { // Subject is male
                // Set formulae
                rWidmark = 0.68;
                rWatson = 0.39834 + ((12.725 * h) / w) - ((0.11275 * a) / w) + (2.8993 / w);
                rForrest = 1.0178 - ((0.012127 * w) / (h * h));
                rSeidl = 0.31608 - (0.004821 * w) + (0.4632 * (h));
                rUlrich = 0.715 - (0.00462 * w) + (0.22 * h);

                // Average together to produce r value
                r = 0.2 * (rWidmark + rWatson + rForrest + rSeidl + rUlrich);

            } else { // Subject is female
                // Set formulae
                rWidmark = 0.55;
                rWatson = 0.29218 + ((12.666 * h) / w) - (2.4846 / w);
                rForrest = 0.8736 - ((0.0124 * w) / (h * h));
                rSeidl = 0.31223 - (0.006446 * w) + (0.4466 * (h));

                // Average together to produce r value
                r = 0.25 * (rWidmark + rWatson + rForrest + rSeidl);
            }

            // Substitute into Widmark's formula and return
            return ((bac * 10) * (r * w) + (elimRate * time)).toFixed(1); 
        },
        calculateBeverage: function () { // Get mililitres of drink
            return Math.round((this.draft.amount_grams / parseFloat(this.draft.beverage_concentration)) / 0.7935);
        },
        /// Sorting methods
        sortClick: function() {
            window.OnClickSort();
        },
        searchSubmit: function () {
            window.OnSearchSubmit();
        },
        // WINDOW methods
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
