// Record component (loop and display for each record)
var ComponentRecord = Vue.component('record', {
    props: ["record", "experiment"],
    template: "<div class='flexbox-row--align margin--dataitem dataitem' style='min-height: 73px;'><i class='material-icons list-icon' style='width: 20%; margin-right: 20px; margin-left: 5px'>assignment_ind</i><div class='flexbox-column--align'><div class='flexbox-row--alignleft'><h5 class='nomargin' style='text-align: left; font-size: 16pt'>{{experiment.name}}-{{record.subject_code}}</h5></div><div class='flexbox-row--alignleft'><h3 class='nomargin' style='text-align: left;'>{{record.display_date}}</h3></div></div></div>"
});

// Dropdown component (loop and display for each dropdown)
var ComponentDropdown = Vue.component('dropdown', {
    props: ["obj"],
    template: '<h6 class="selectable dropdown-option">{{obj.name}}</h6>'
});

// Vue instance
let vm = new Vue({
    el: '#vm', // Container ID 
    data: {
        records: [ // List of all records from DB

        ],
        searchRecords: [ // List of all records currently matching search query

        ],
        experiments: [ // List of all experiments fetched from DB

        ],
        beverages : [ // List of all beverages fetched from DB

        ],
        // Male gender for dropdown component
        gender_male: {
            name: "Male",
            raw: true
        },
        // Female gender dropdown component
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
        experimentSelected: {}, // Currently selected experiment in modal
        experiment: {}, // Currently loaded experiment
        settingsBeverage: { // Beverage settings selected in modal
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
            alcvol: "",
            actual_bac: "",
            actual_bac_time: "",
            beverage_name: "",
            beverage_concentration: ""
        }, 
        selected: { // Currently selected record
            subject_code: "",
            beverage_name: ""
        },
        validated: { // Store whether certain values are validated
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
        reportDownloadIsSuccessful: null,
        // Yeah it's a B64 string, the framework doesn't yet support conversion inside the JS :)
        reportB64: "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",
        fileMenuHeight: "135px", // Default height for file menu (changes if user not Admin because 'Experimenter' option not displayed)
        searchText: "", // Current text in search menu
        sortCycle: 0, // Current sort cycle
        areYouSureCallback: null, // Callback for are you sure menu
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
    components: { // Register the components
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
                    let recordsDates = this.records.filter(r => r.display_date.includes(this.searchText));
                    
                    // Loop through pulled records and add them to search records
                    for (i = 0; i < records.length; i++) {
                        this.searchRecords.push(records[i]);
                    }
                    for (i = 0; i < recordsDates.length; i++) { // Loop through dates
                        // Make sure no double ups occur and add
                        let index = records.map((r) => r.id).indexOf(recordsDates[i].id);
                        if (index == -1) {
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
        // On initial load
        initialLoad: function () {
            // Get user (from database using C++ interface)
            let user = window.OnGetUser();
            this.user = {
                id: parseInt(user[0]),
                firstName: user[1],
                lastName: user[2],
                accessLevel: parseInt(user[3])
            };

            // Get experiments (from database using C++ interface)
            let exps = window.OnLoadExperiments();
            for (i = 0; i < exps.length; i++) {
                this.experiments.push({id: exps[i][0], 
                    name: exps[i][1]});
            }

            // Get beverages (from database using C++ interface)
            this.loadBeverages();

            // Set file menu height to fit menu item if adminstrator access
            if (this.user.accessLevel == 2) {
                this.fileMenuHeight = "158px";
            }
        },
        // On load beverages
        loadBeverages: function () {
            // Get beverages from DB
            let bevs = window.OnLoadBeverages();

            // Assign beverages
            for (i = 0; i < bevs.length; i++) {
                this.beverages.push({id: bevs[i][0],
                name: bevs[i][1],
                concentration: bevs[i][2]});
            }
        },
        // On load subjects
        loadSubjects: function () {
            // Reset records
            this.records = [];

            // Load subjects from DB
            let subjects = window.OnLoadSubjects(this.experiment.id);
                
            // Assign subjects
            for (i = 0; i < subjects.length; i++) {
                this.records.push({id: subjects[i][0], 
                    subject_code: subjects[i][1], 
                    created_on: subjects[i][2].split(" "),
                    display_date: subjects[i][2].split(" ")[0].split('-').reverse().join('/')});
            }
        },
        // On load experiment
        loadExp: function () {
            // Load subjects if experiment has been chosen
            if (this.experimentSelected.id != null) {
                // Bind to actual experiment
                this.experiment = Object.assign({}, this.experimentSelected);               
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
        // On click sidebar record
        recordClick: function (event, record) {
            // Reset selected
            this.resetSelected();
            // Reset report download checker
            this.reportDownloadIsSuccessful = null;
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
                // Get the subject from DB
                let subject = window.OnClickRecord(record.id);
                
                // Cut off seconds from time (no need to be so precise)
                let splitTime = subject[13].split(" ")[1].split(":");
                splitTime = splitTime[0] + ":" + splitTime[1];

                // Set selected object
                this.selected = {id: subject[0], 
                    subject_code: subject[1], 
                    age: subject[2],
                    height: parseInt(subject[3]),
                    weight: parseFloat(subject[4]).toFixed(1),
                    gender: parseInt(subject[5]) == 1 ? "Male" : "Female",
                    created_on: subject[6].split(" ")[0],
                    target_bac: parseFloat(subject[7]).toFixed(3),
                    target_bac_time: subject[8],
                    amount_grams: parseFloat(subject[9]).toFixed(1),
                    amount_beverage: parseFloat(subject[10]).toFixed(1),
                    alcvol: parseFloat(subject[11]).toFixed(1),
                    actual_bac: parseFloat(subject[12]).toFixed(3),
                    actual_bac_time: splitTime,
                    beverage_name: subject[14],
                    beverage_concentration: parseFloat(subject[15]).toFixed(3)};
                
                // Set screens
                this.isNewStart = false;
                this.isBacMode = false;
                this.isViewingSubject = true;
            }
        },
        // On save subject
        saveSubject: function () {
            // Define return array
            let returnArray = [];

            // Push items
            returnArray.push(this.draft.subject_code);
            returnArray.push(this.user.id);
            returnArray.push(this.experiment.id);
            returnArray.push(this.draft.age);
            returnArray.push(this.draft.gender == "Male" ? 1 : 0);
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
            returnArray.push(this.draft.alcvol)
            returnArray.push(this.draft.actual_bac);
            returnArray.push(this.draft.actual_bac_time);

            // Send to database through C++ interface
            window.OnAddNewSubject(returnArray);
        },
        // On reset selected object
        resetSelected: function () {
            // Reset selected
            this.selected = {
                subject_code: ""
            };
        },
        // On cancel subject creation
        cancelSubject: function () {
            // Annul draft values
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
                alcvol: "",
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

            // Remove the draft sidebar record from the front of the array
            this.records.shift();

            // Reset screen
            this.isNewStart = true;
            this.isCalculateClicked = false;
        },
        // On click calculate
        calculateClick: function () {
            // Store whether validation fails
            let invalid = false; 
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

            // Create return array
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
        // Show s at end of 'hour' if more than 1 hour
        checkPlural: function (i) {
            // Return 'hours' if greater than 1
            if (i > 1) return "hours";

            // Otherwise return 'hour'
            return "hour";
        },
        // On click administered
        administeredClick: function () {        
            // Set created on time
            this.draft.created_on = this.getDateNow();

            // Reset calculated check
            this.isCalculateClicked = false;

            // Change screen
            this.isBacMode = true;
        },
        // On record BAC
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

            // Set concentration
            this.draft.alcvol = this.draft.beverage_concentration;

            // Save the subject
            this.saveSubject();

            // Parse float
            this.draft.actual_bac = parseFloat(this.draft.actual_bac);

            // Set selected to the draft
            this.selected = Object.assign({}, this.draft);

            // Cut off seconds (no need to be that precise)
            let splitTime = date.split(" ")[1].split(":");
            this.selected.actual_bac_time = splitTime[0] + ":" + splitTime[1];

            // Annul draft values
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
                alcvol: "",
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
        // On click download report
        reportDownload: function () {
            // Call the method and pass through document title
            let res = window.OnClickDownloadReport("Report for " + this.experiment.name + "-" + this.selected.subject_code + ".pdf");
            
            // Set success/fail message
            if (parseInt(res) === 0) {
                this.reportDownloadIsSuccessful = true;
            } else {
                this.reportDownloadIsSuccessful = false;
            }
        },
        // Get report data
        getReportData: function () {
            // Create new document
            let doc = new jsPDF();

            // Convert image
            /*let binaryString = window.atob(this.reportB64);
            let len = binaryString.length;
            let bytes = new Uint8Array(len);
            for (let i = 0; i < len; i++) {
                bytes[i] = binaryString.charCodeAt(i);
            }
            doc.internal.scaleFactor = 1.33;
            doc.addImage(bytes, "PNG", 100, 15, 90, 13.87);*/
            //doc.internal.scaleFactor = 1.0;

            // Set header text
            doc.setFontSize(28);
            doc.setFont("helvetica", "bold");
            doc.setTextColor(253,115,14);
            doc.text("Report for " + this.experiment.name + "-" + this.selected.subject_code, 104, 40, null, null, "center");

            // Set subheader text
            doc.setTextColor(0,0,0);
            doc.setFontSize(18);
            doc.text("Subject Details", 20, 65);
            doc.text("Analysis of Consumption", 20, 115);
            
            // Underline the subheaders
            doc.setLineWidth(0.5);
            let textWidth = doc.getTextWidth("Subject Details");
            doc.line(20, 66, 20 + textWidth, 66);
            textWidth = doc.getTextWidth("Analysis of Consumption");
            doc.line(20, 116, 20 + textWidth, 116);

            // Set labels for subject details
            doc.setFontSize(14);
            doc.text("Age:", 20, 80);
            doc.text("Gender:", 20, 90);
            doc.text("Height:", 110, 80);
            doc.text("Weight:", 110, 90);
            
            // Set values for subject details
            doc.setFont("helvetica", "normal")
            doc.text(this.selected.age, 45, 80);
            doc.text(this.selected.gender, 45, 90);
            doc.text(this.selected.height + " cm", 135, 80);
            doc.text(this.selected.weight + " kg", 135, 90);
            
            // Set labels for analysis
            doc.setFont("helvetica", "bold");
            doc.text("Target BAC:", 20, 130);
            doc.text("Alcohol Consumption:", 20, 141);
            doc.text("Measured in " + this.selected.beverage_name + ":", 20, 152);
            doc.text("Alcohol Concentration:" , 20, 163);
            doc.text("Actual BAC:", 20, 174);
            
            // Set values for analysis
            doc.setFont("helvetica", "normal")
            doc.text(this.selected.target_bac + "%", 85, 130);
            doc.text(this.selected.amount_grams + " g", 85, 141);
            doc.text(this.selected.amount_beverage + " ml", 85, 152);
            doc.text((this.selected.alcvol * 100).toFixed(1) + "% vol/vol", 85, 163);
            doc.text(this.selected.actual_bac + "%", 85, 174);
            
            // Set footer text and date
            doc.setFont("helvetica", "italic")
            doc.text("This report generated by Alcolator: BAC Calculation in Laboratory Environments", 104, 270, null, null, "center");
            let date = this.getDateNow().split(" ")[0].split("-").reverse().join("/");
            doc.text("on " + date + ".", 104, 280, null, null, "center");
            
            // Return the buffer
            return doc.output("arraybuffer");
        },
        // Set the gender for the draft
        setGender: function (event, gender) {
            this.draft.gender = gender;
        },
        // Get current date in database ISO format
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
        // On click file menu
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
        // On hide file menu
        fileMenuHide: function (event) {
            // Get menu & target from DOM
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
        // On click administration mode button
        fileClickAdmin: function () {
            // Change modes
            window.OnClickAdminMode();
        },
        // On click new subject button
        fileNewSubject: function () {
            this.isEnterSubjectOpen = true;
        },
        // On close new subject modal
        newSubjectClose: function () {
            this.isEnterSubjectOpen = false;
            this.isNewStart = true;
        },
        // On create new subject entry
        newSubject: function () {
            // Check if there is a number with regex
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

            // Add new card to top of record sidebar
            this.records.unshift({
                id: this.records.length + 1, 
                subject_code: this.draft.subject_code,
                created_on: date,
                display_date: date[0].split('-').reverse().join('/'),
                draft: true
            });

            // Add subject code to selected object
            this.selected.subject_code = this.draft.subject_code;

            // Set screens
            this.isEnterSubjectOpen = false;
            this.isNewStart = false;
            this.isViewingSubject = false;
        },
        // On open load experiment modal
        fileLoadExp: function () {
            this.isLoadExperimentOpen = true;
        },
        // On choose experiment
        chooseExperiment: function (event, experiment) {
            this.isExperimentLoaded = false; // Mark as not loaded
            this.experimentSelected = {id: experiment.id, name: experiment.name}; // Add to active selection            
        },
        // On close load experiment modal
        loadExpClose: function () {
            this.isLoadExperimentOpen = false;
        },
        // On log out
        fileLogOut: function () {
            // Log out
            window.OnLogOut();
        },
        // On open settings modal
        settingsOpen: function () {
            // Open
            this.isSettingsMenuOpen = true;            
        },
        // On close settings modal
        settingsClose: function () {
            // Annul beverage values
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

            // Close modal
            this.isSettingsMenuOpen = false; 
        },
        // On save settings
        settingsSave: function () {
            // Store whether validation fails
            let invalid = false;

            // Existing concentration
            if (this.settingsBeverage.concentration == "") {
                // Continue if empty
                invalid = false;
            } else if (isNaN(this.settingsBeverage.concentration.toString())) {
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
            } else if (isNaN(this.settingsBeverage.newConc.toString())) {
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

            // Define return array
            let returnArray = [];

            // Push values
            returnArray.push(this.settingsBeverage.id);
            returnArray.push(this.settingsBeverage.newName);
            returnArray.push(parseFloat(this.settingsBeverage.newConc).toFixed(1) / 100); // Store as decimal not int
            returnArray.push(this.settingsBeverage.name);
            returnArray.push(parseFloat(this.settingsBeverage.concentration).toFixed(1) / 100); // Store as decimal not int
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

            // Annul settings values
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
        // On choose beverage
        chooseBeverage: function (event, beverage) {
            // Add to settings object
            this.settingsBeverage.id = beverage.id;
            this.settingsBeverage.name = beverage.name;
            this.settingsBeverage.concentration = parseFloat(beverage.concentration) * 100;
        },
        // On choose beverage in subject window
        chooseBeverageSubject: function (event, beverage) {
            // Add to draft values
            this.draft.beverage_name = beverage.name;
            this.draft.beverage_concentration = beverage.concentration;
        },
        // On delete beverage
        deleteBeverage: function () {
            // Delete
            window.OnDeleteBeverage(this.settingsBeverage.id);

            // Annul settings values
            this.settingsBeverage.id = null;
            this.settingsBeverage.name = "";
            this.settingsBeverage.concentration = "";
            
            // Reset array and reload beverages
            this.beverages = [];
            this.loadBeverages();
        },
        // Check whether not a number or a decimal
        isNotNumberOrIsDecimal: function (data) {
            // If not number
            if (isNaN(data)) return true;
            
            // If not decimal
            if (data.indexOf('.') != -1) return true;

            // Otherwise
            return false;
        },
        // On click sort button
        sortClick: function() {
            // Increment sort counter
            if (this.sortCycle == 0 || this.sortCycle != 4) { // Increment counter if start or not end of toggle
                this.sortCycle++;
            } else { // Go back to first cycle if already 4
                this.sortCycle = 1;
            }

            // Sort elements depending on cycle
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
        // On click search button
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
            this.isSearchOpen = true;
        },
        // On click outside search box
        searchHide: function (event) {
            // Get menu & target element
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
        // On open are you sure modal
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
        // On click yes
        areYouSureYes: function () {
            // Run the callback
            this.areYouSureCallback();

            // Close window
            this.isAreYouSureOpen = false;
        },
        // On click no
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
    // On instance created
    created () {
        // Add the click listeners for file menu and search menu hide
        document.addEventListener('click', this.fileMenuHide);
        document.addEventListener('click', this.searchHide);
    },
    // On instance destroyed
    destroyed () {
        // Remove the click listeners for file menu and search menu hide
        document.removeEventListener('click', this.fileMenuHide);
        document.removeEventListener('click', this.searchHide);
    }
});
