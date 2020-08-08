// Record component
var ComponentRecord = Vue.component('record', {
    props: ["record", "experiment"],
    template: "<div class='flexbox-row--align margin--dataitem dataitem' style='min-height: 73px;'><i class='material-icons list-icon' style='width: 20%; margin-right: 20px; margin-left: 5px'>assignment_ind</i><div class='flexbox-column--align'><div class='flexbox-row--alignleft'><h5 class='nomargin' style='text-align: left; font-size: 16pt'>{{experiment.name}}-{{record.subject_code}}</h5></div><div class='flexbox-row--alignleft'><h3 class='nomargin' style='text-align: left;'>{{record.display_date}}</h3></div></div></div>"
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
        searchRecords: [

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
            id: -1,
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
            subject_code: "",
            beverage_name: ""
        }, // Currently selected record
        validated: {
            age: true,
            height: true,
            weight: true,
            target_bac: true,
            target_bac_time: true,
            actual_bac: true,
            newBeverage: true,
            changeBeverage: true,
            newSubjectCode: true
        },
        fileMenuHeight: "135px",
        searchText: "",
        sortCycle: 0,
        areYouSureCallback: null,
        isExperimentLoaded: false, // Is an experiment loaded
        isCalculateClicked: false, // Is the calculate button clicked
        isNewStart: true, // Program just started
        isBacMode: false, // Subject is in BAC mode
        isViewingSubject: false, // Subject is being viewed
        isFileMenuOpen: false, // File menu is open
        isSearchOpen: false, // Search bar is open
        isSearchActive: false, // Is the search bar being typed in
        isSettingsMenuOpen: false, // Settings menu is open
        isEnterSubjectOpen: false, // Menu for entering subject code is open
        isLoadExperimentOpen: false, // Menu for loading experiment is open
        isAreYouSureOpen: false // Is the are you sure window open        
    },
    components: {
        'record': ComponentRecord,
        'dropdown': ComponentDropdown
    },
    watch: { 
        // Search whilst typing
        searchText: function (value) { 
            // Clear search records
            this.searchRecords = [];

            // Check if empty
            if (value != "") {
                // Box is not empty, search is active
                this.isSearchActive = true; 
            } else {
                // Box is empty, search is inactive
                this.isSearchActive = false;
            }

            // If search is active
            if (this.isSearchActive) {
                // Check if a number
                if (!isNaN(this.searchText)) {
                    // Get corresponding subject IDs and dates
                    let records = this.records.filter(r => r.subject_code.includes(this.searchText.toLowerCase()));
                    let recordsDates = this.records.filter(r => r.created_on.join(" ").includes(this.searchText));
                    
                    // Loop through pulled records and add them to search records
                    for (i = 0; i < records.length; i++) {
                        this.searchRecords.push(records[i]);
                    }
                    for (i = 0; i < recordsDates.length; i++) {
                        // Make sure no double ups occur
                        let index = records.map((r) => r.id).indexOf(recordsDates[i].id);
                        if (index != -1) {
                            this.searchRecords.push(recordsDates[i]);
                        }
                    }
                } else { // It's not a number, so it's a subject ID or a date
                    if (this.searchText.includes('/') || this.searchText.includes('-')) {
                        // It might be a date, so format the string into date format if includes a '/' instead of a '-'
                        let tempText = "";
                        if (this.searchText.includes('/')) {
                            tempText = this.searchText.split('/').join("-");
                        }

                        // Get records
                        let records = this.records.filter(r => r.created_on.join(" ").includes(tempText));
                        // Loop through pulled records and add them to search records
                        for (i = 0; i < records.length; i++) {
                            this.searchRecords.push(records[i]);
                        }
                    } else {
                        // Not a date, so search subject IDs
                        let records = this.records.filter(r => r.subject_code.toLowerCase().includes(this.searchText.toLowerCase()));
                        
                        // Loop through pulled records and add them to search records
                        for (i = 0; i < records.length; i++) {
                            this.searchRecords.push(records[i]);
                        }
                    }
                }
            }
        }
    },
    methods: {
        /// Data events
        initialLoad: function () {
            // Get user
            let user = window.OnGetUser();
            this.user = {
                id: parseInt(user[0]),
                firstName: user[1],
                lastName: user[2],
                accessLevel: parseInt(user[3])
            };

            // Get experiments
            let exps = window.OnLoadExperiments();
            for (i = 0; i < exps.length; i++) {
                this.experiments.push({id: exps[i][0], 
                    name: exps[i][1]});
            }

            // Get beverages
            this.loadBeverages();

            // Set file menu height to fit menu item if adminstrator access
            if (this.user.accessLevel == 2) {
                this.fileMenuHeight = "158px";
            }
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
                    created_on: subjects[i][2].split(" "),
                    display_date: subjects[i][2].split(" ")[0].split('-').reverse().join('/')});
            }
        },
        loadExp: function () {
            // Display subjects if experiment has been chosen
            if (this.experiment.id != null) {
                this.isExperimentLoaded = true;
                this.loadSubjects();
                // Hide experiment window
                this.isLoadExperimentOpen = false;
            }

            // Reset selected & screens
            this.resetSelected();
            this.isNewStart = true;
            this.isViewingSubject = false;
            this.isBacMode = false;
            this.isCalculateClicked = false;
        },
        recordClick: function (event, record) {
            // Reset selected
            this.resetSelected();
            // If it is the draft
            if (record.subject_code == this.draft.subject_code) {
                // Set the subject code and beverage name
                this.selected.subject_code = this.draft.subject_code;
                this.selected.beverage_name = this.draft.beverage_name.toLowerCase();
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

            // Reset validation
            this.validated.age = true;
            this.validated.height = true;
            this.validated.weight = true;
            this.validated.target_bac = true;
            this.validated.target_bac_time = true;

            // Remove the draft sidebar record
            this.records.shift();

            // Reset screen
            this.isNewStart = true;
            this.isCalculateClicked = false;
            
        },
        calculateClick: function () {
            let invalid = false; // Hold whether anything is invalid
            // Age
            if (this.isNotNumberOrIsDecimal(this.draft.age)) {
                // If NaN or decimal
                this.validated.age = false;
                invalid = true;
            } else if (parseInt(this.draft.age) < 18 || parseInt(this.draft.age) > 75) {
                // If outside range
                this.validated.age = false;
                invalid = true;
            } else {
                // All good
                this.validated.age = true;
            }

            // Height
            if (this.isNotNumberOrIsDecimal(this.draft.height)) {
                // If NaN or is decimal
                this.validated.height = false;
                invalid = true;
            } else if (parseInt(this.draft.height) < 130 || parseInt(this.draft.height) > 200) {
                // If outside range
                this.validated.height = false;
                invalid = true;
            } else {
                // All good
                this.validated.height = true;
            }

            // Weight
            if (isNaN(this.draft.weight)) {
                // If NaN
                this.validated.weight = false;
                invalid = true;
            } else if (parseFloat(this.draft.weight) < 35 || parseFloat(this.draft.weight) > 150) {
                // If outside range
                this.validated.weight = false;
                invalid = true;
            } else {
                // All good
                this.validated.weight = true
            }

            // Target BAC
            if (isNaN(this.draft.target_bac)) {
                // If NaN
                this.validated.target_bac = false;
                invalid = true;
            } else if (parseFloat(this.draft.target_bac) < 0 || parseFloat(this.draft.target_bac) > 0.15) {
                // If outside range
                this.validated.target_bac = false;
                invalid = true;
            } else {
                // All good
                this.validated.target_bac = true
            }

            // Target BAC Time
            if (isNaN(this.draft.target_bac_time)) {
                // If NaN
                this.validated.target_bac_time = false;
                invalid = true;
            } else if (parseFloat(this.draft.target_bac_time) < 0 || parseFloat(this.draft.target_bac_time) > 8) {
                // If outside range
                this.validated.target_bac_time = false;
                invalid = true;
            } else {
                // All good
                this.validated.target_bac_time = true;
            }

            // Don't send values for calculation if anything invalid
            if (invalid) return;

            // Create array
            let sendValues = [];

            // Push all values for calculation
            sendValues.push(this.draft.target_bac);
            sendValues.push(this.draft.weight);
            sendValues.push(this.draft.height);
            sendValues.push(this.draft.age);
            sendValues.push(this.draft.gender == "Male" ? 1 : 0);
            sendValues.push(this.draft.target_bac_time);
            sendValues.push(this.draft.beverage_concentration);

            // Assign selected beverage
            this.selected.beverage_name = this.draft.beverage_name.toLowerCase();

            // Parse float
            this.draft.target_bac = parseFloat(this.draft.target_bac);

            // Calculate and assign
            let values = window.OnClickCalculate(sendValues);
            this.draft.amount_grams = parseFloat(values[0]).toFixed(1);
            this.draft.amount_beverage = values[1];
            
            // Show administer button
            this.isCalculateClicked = true;
        },
        checkPlural: function (i) {
            // Return 'hours' if greater than 1
            if (i > 1) return "hours";

            // Otherwise return 'hour'
            return "hour";
        },
        administeredClick: function () {        
            // Set created on time
            this.draft.created_on = this.getDateNow();

            // Reset calculated check
            this.isCalculateClicked = false;
            // Change screen
            this.isBacMode = true;
        },
        bacRecord: function () {
            // Catch invalid input for actual BAC
            if (isNaN(this.draft.actual_bac)) {
                // If NaN
                this.validated.actual_bac = false;
                return;
            } else if (parseFloat(this.draft.actual_bac) < 0 || parseFloat(this.draft.actual_bac) > 0.15) {
                // If outside range
                this.validated.actual_bac = false;
                return;
            } else {
                // All good
                this.validated.actual_bac = true
            }            

            // Get current date
            let date = this.getDateNow();
            // Set actual BAC datetime
            this.draft.actual_bac_time = date;

            // Save the subject
            this.saveSubject();

            // Parse float
            this.draft.actual_bac = parseFloat(this.draft.actual_bac);

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
        fileClickAdmin: function () {
            // Change modes
            window.OnClickAdminMode();
        },
        fileNewSubject: function () {
            this.isEnterSubjectOpen = true;
        },
        newSubjectClose: function () {
            this.isEnterSubjectOpen = false;
            this.isNewStart = true;
        },
        newSubject: function () {
            // Check if there is a number
            if (!/\d/.test(this.draft.subject_code)) {
                // There is no number, validation failed
                this.validated.newSubjectCode = false;
                return;
            } else {
                // All good
                this.validated.newSubjectCode = true;
            }
            // Get current datetime and format
            let date = this.getDateNow().split(" ");
            // Add new card
            this.records.unshift({
                id: this.records.length + 1, 
                subject_code: this.draft.subject_code,
                created_on: date,
                draft: true
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
            // Log out
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
            // Reset validation
            this.validated.newBeverage = true;
            this.validated.changeBeverage = true;
            // Close menu
            this.isSettingsMenuOpen = false; 
        },
        settingsSave: function () {
            // Record whether validation fails
            let invalid = false;
            // Existing concentration
            if (this.settingsBeverage.concentration == "") {
                // Continue if empty
                invalid = false;
            } else if (isNan(this.settingsBeverage.concentration.toString())) {
                // If NaN or is decimal
                this.validated.changeBeverage = false;
                invalid = true;
            } else if (parseFloat(this.settingsBeverage.concentration) < 0 || parseFloat(this.settingsBeverage.concentration) > 100) {
                // If outside range
                this.validated.changeBeverage = false;
                invalid = true;
            } else {
                // All good
                this.validated.changeBeverage = true;
            }
            // New concentration
            if (this.settingsBeverage.newConc == "") {
                // Continue if empty
                invalid = false;
            } else if (isNan(this.settingsBeverage.newConc.toString())) {
                // If NaN or is decimal
                this.validated.newBeverage = false;
                invalid = true;
            } else if (parseFloat(this.settingsBeverage.newConc) < 0 || parseFloat(this.settingsBeverage.newConc) > 100) {
                // If outside range
                this.validated.newBeverage = false;
                invalid = true;
            } else {
                // All good
                this.validated.newBeverage = true;
            }

            // Don't save if invalid
            if (invalid) return;

            // Define return array and push values
            let returnArray = [];
            // Return ID if edited and -1 if not
            returnArray.push(this.settingsBeverage.id);
            returnArray.push(this.settingsBeverage.newName);
            returnArray.push(parseInt(this.settingsBeverage.newConc) / 100);
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
        deleteBeverage: function () {
            // Delete
            window.OnDeleteBeverage(this.settingsBeverage.id);

            // Reset values
            this.settingsBeverage.id = null;
            this.settingsBeverage.name = "";
            this.settingsBeverage.concentration = "";
            
            // Reset array and reload
            this.beverages = [];
            this.loadBeverages();
        },
        isNotNumberOrIsDecimal: function (data) {
            // If not number
            if (isNaN(data)) return true;
    
            // Otherwise
            return false;
        },
        /// Sorting methods
        sortClick: function() {
            // Increment sort counter
            if (this.sortCycle == 0 || this.sortCycle != 4) { // Increment counter if start or not end of toggle
                this.sortCycle++;
            } else { // Go back to first cycle if already 4
                this.sortCycle = 1;
            }

            // Sort elements
            if (this.sortCycle == 1) {
                // Sort by code descending (numbers)
                this.records.sort((a, b) => parseInt(b.subject_code.replace(/\D/g, '')) - parseInt(a.subject_code.replace(/\D/g, '')));
            } else if (this.sortCycle == 2) {
                // Sort by code ascending (numbers)
                this.records.sort((a, b) => parseInt(a.subject_code.replace(/\D/g, '')) - parseInt(b.subject_code.replace(/\D/g, '')));
            } else if (this.sortCycle == 3) {
                // Sort by date descending (descending)
                this.records.sort(function(a, b) {
                    // Split the elements into an array
                    dateString1 = a.created_on.join('-').split(':').join('-').split('-');
                    dateString2 = b.created_on.join('-').split(':').join('-').split('-');
                    
                    // Create dates
                    date1 = new Date(parseInt(dateString1[0]), parseInt(dateString1[1]), parseInt(dateString1[2]), parseInt(dateString1[3]), parseInt(dateString1[4]), parseInt(dateString1[5]));
                    date2 = new Date(parseInt(dateString2[0]), parseInt(dateString2[1]), parseInt(dateString2[2]), parseInt(dateString2[3]), parseInt(dateString2[4]), parseInt(dateString2[5]));

                    // Compare dates
                    return date2 - date1;
                });
            } else {
                // Sort by date ascending (newest)
                this.records.sort(function(a, b) {
                    // Split the elements into an array
                    dateString1 = a.created_on.join('-').split(':').join('-').split('-');
                    dateString2 = b.created_on.join('-').split(':').join('-').split('-');
                    
                    // Create dates
                    date1 = new Date(parseInt(dateString1[0]), parseInt(dateString1[1]), parseInt(dateString1[2]), parseInt(dateString1[3]), parseInt(dateString1[4]), parseInt(dateString1[5]));
                    date2 = new Date(parseInt(dateString2[0]), parseInt(dateString2[1]), parseInt(dateString2[2]), parseInt(dateString2[3]), parseInt(dateString2[4]), parseInt(dateString2[5]));

                    // Compare dates
                    return date1 - date2;
                });
            }
        },
        searchClick: function () {
            // If already open
            if (this.isSearchOpen === true) {
                // Close, clear bar, and return
                this.isSearchOpen = false;
                this.searchText = "";
                this.isSearchActive = false;
                return;
            }
            // Open the search box and focus
            //this.$refs.searchBox.$el.focus();
            this.isSearchOpen = true;
        },
        searchHide: function (event) {
            // Get menu & target
            let element = this.$refs.searchBox;
            let target = event.target;
            // Check if the target is the file button
            if (target.id === "searchBtn") {
                // Skip next block
                return;
            }
            // If click outside the menu
            if ((element !== target) && !element.contains(target)) {
                // Close menu
                this.isSearchOpen = false;
                // Clear search box
                this.searchText = "";
                this.isSearchActive = false;
            }
        },
        areYouSureOpen: function (callback) {
            // Set the callback
            this.areYouSureCallback = callback;

            // Close modals
            this.isSettingsMenuOpen = false;
            this.isLoadExperimentOpen = false;
            this.isEnterSubjectOpen = false;

            // Open the window
            this.isAreYouSureOpen = true;
        },
        areYouSureYes: function () {
            // Run the callback
            this.areYouSureCallback();

            // Close window
            this.isAreYouSureOpen = false;
        },
        areYouSureNo: function () {
            // Clear the callback
            this.areYouSureCallback = null;

            // Close the window
            this.isAreYouSureOpen = false;
        },
        // WINDOW methods
        winClose: function () {
            window.OnWindowClose();
        }
    },
    created () {
        // Add the click listeners
        document.addEventListener('click', this.fileMenuHide);
        document.addEventListener('click', this.searchHide);
    },
    destroyed () {
        // Remove the click listener
        document.removeEventListener('click', this.fileMenuHide);
        document.removeEventListener('click', this.searchHide);
    }
});
