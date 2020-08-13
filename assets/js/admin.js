// Record component (loops and adds one for each user)
var ComponentUser = Vue.component('user', {
    props: ["user"],
    template: '<div class="flexbox-row--align margin--dataitem dataitem" style="min-height: 73px;"><i class="material-icons list-icon" style="width: 20%; margin-right: 20px; margin-left: 5px">assignment_ind</i><div class="flexbox-column--align"><div class="flexbox-row--alignleft"><h5 class="nomargin" style="text-align: left; font-size: 14pt;">{{user.firstName}} {{user.lastName}}</h5></div><div class="flexbox-row--alignleft"><h3 class="nomargin" style="text-align: left;">{{user.accessLevelFull}}</h3></div></div></div>'
});

// Dropdown component (loops and adds one for each dropdown record)
var ComponentDropdown = Vue.component('dropdown', {
    props: ["obj"],
    template: '<h6 class="dropdown-option selectable">{{obj}}</h6>'
});

// Vue instance
let vm = new Vue({
    el: '#vm', // Container ID 
    data: {
        users: [ // Array of users pulled from DB

        ],
        searchUsers: [ // Array of users currently fitting search criteria

        ],
        experiments: [ // Array of experiments pulled from DB

        ],
        accessLevels: { // Different access levels for display
            observer: "Data Observer",
            experimenter: "Experimenter",
            administrator: "Administrator"
        },
        user: { // Current user in session
            id: -1,
            firstName: "",
            lastName: "",
            username: "",
            accessLevel: "",
        }, 
        draft: { // Current user being drafted
            firstName: "",
            lastName: "",
            accessLevel: "",
            accessLevelFull: "",
            username: "",
            password: "",
            active: false
        },
        selected: { // Currently selected user
            
        },
        areYouSureCallback: null, // Callback for are you sure menu
        viewName: "", // Display name when viewing subject
        searchText: "", // Text for search
        experimentCode: "", // Code for new experiment
        isNewStart: true, // Program just started
        isFileMenuOpen: false, // File menu open
        isNewUserOpen: false, // New user open
        isViewingUser: false, // Is viewing a user
        isSearchOpen: false, // Check if search is open
        isSearchActive: false, // Check if currently typing
        isNewExperimentOpen: false, // Check if new experiment window is open
        isAreYouSureOpen: false // Check if are you sure prompt is open
    },
    components: { // Register the components
        'record': ComponentUser,
        'dropdown': ComponentDropdown
    },
    watch: { 
        // Search whilst typing
        searchText: function (value) { 
            // Clear search records
            this.searchUsers = [];

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
                // Get names and access codes
                let users = this.users.filter(u => u.firstName.toLowerCase().includes(this.searchText.toLowerCase()) || u.lastName.toLowerCase().includes(this.searchText.toLowerCase()));

                // Loop through found users and push
                for (i = 0; i < users.length; i++) {
                    this.searchUsers.push(users[i]);
                }
            }
        }
    },
    methods: {
        // On initial page load
        initialLoad: function () {
            // Get user (object sent from C++ database interface)
            let user = window.OnGetUser();
            this.user = {
                id: parseInt(user[0]),
                firstName: user[1],
                lastName: user[2],
                username: user[3],
                accessLevel: parseInt(user[4])
            };

            // Get users (array sent from C++ database interface)
            let users = window.OnLoadUsers();
            for (i = 0; i < users.length; i++) {
                this.users.push({
                    id: users[i][0], 
                    firstName: users[i][1],
                    lastName: users[i][2],
                    accessLevel: users[i][3],
                    accessLevelFull: this.switchAccessLevel(parseInt(users[i][3])),
                    username: users[i][4]
                });
            }

            // Get experiments (array sent from C++ database interface)
            let exps = window.OnLoadExperiments();
            for (i = 0; i < exps.length; i++) {
                this.experiments.push({
                    id: exps[i][0], 
                    name: exps[i][1]
                });
            }
        },
        // Loading users from DB
        loadUsers: function () {
            // Empty users array to avoid double up
            this.users = [];
            // Get users from DB
            let users = window.OnLoadUsers();
            for (i = 0; i < users.length; i++) {
                this.users.push({
                    id: users[i][0], 
                    firstName: users[i][1],
                    lastName: users[i][2],
                    accessLevel: users[i][3],
                    accessLevelFull: this.switchAccessLevel(parseInt(users[i][3])),
                    username: users[i][4]
                });
            }
        },
        // Open file menu
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
        // Hide file menu
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
        // Create new user draft
        fileNewUser: function () {
            // Add new card
            this.users.unshift({
                id: this.users.length + 1, 
                firstName: "New",
                lastName: "User",
                accessLevel: this.draft.accessLevel,
                accessLevelFull: "Draft",
                username: this.draft.username,
                draft: true
            });
            // Set screens
            this.isNewStart = false;
            this.isViewingUser = false;
            this.isNewUserOpen = true;
        },
        // Add new experiment (file menu modal)
        fileNewExp: function () {
            // Set screens
            this.isNewExperimentOpen = true;
        },
        // Close new experiment modal
        newExperimentClose: function () {
            // Set screens
            this.isNewExperimentOpen = false;
        },
        // Make call to C++ and go into experimenter mode
        fileExpMode: function () {
            window.OnClickExperimenterMode()
        },
        // Log out of app
        fileLogOut: function () {
            window.OnLogOut();
        },
        // On click user
        userClick: function (event, user) {
            // Reset selected
            this.resetSelected();
            
            // Check if draft is active
            if (user.draft) {
                // Reset screen
                this.isViewingUser = false;
                this.isNewUserOpen = true;
            } else {
                // If user is admin, set variable
                if (user.accessLevel == 2) {
                    this.isSelectedAdmin = true;
                } else {
                    this.isSelectedAdmin = false;
                }

                // Assign user to the selected object
                this.selected = {
                    id: user.id,
                    firstName: user.firstName,
                    lastName: user.lastName,
                    accessLevel: user.accessLevel,
                    accessLevelFull: user.accessLevelFull,
                    username: user.username,
                    password: user.password
                }
                
                // Assign display name
                this.viewName = user.firstName + " " + user.lastName;

                // Set screens
                this.isViewingUser = true;
                this.isNewStart = false;
                this.isNewUserOpen = false;
            }
        },
        // On reset selected
        resetSelected: function () {
            // Reset selected
            this.selected = {
                subject_code: ""
            };
        },
        // On save new user
        saveNewUser: function() {
            // Draft is no longer active
            this.draft.active = false;

            // Define return array
            let returnArray = [];

            // Push items
            returnArray.push(this.draft.firstName);
            returnArray.push(this.draft.lastName);
            returnArray.push(this.draft.accessLevel);
            returnArray.push(this.draft.username);
            returnArray.push(this.draft.password);

            // Send the array to the database
            window.OnSaveUser(returnArray);

            // Deactivate draft
            this.selected.draft = false;

            // Set screens
            this.isNewUserOpen = false;
            this.isViewingUser = true;

            // Set selected object to the draft
            this.selected = Object.assign({}, this.draft);
            this.viewName = this.draft.firstName + " " + this.draft.lastName;

            // Annul draft values
            this.draft = {
                firstName: "",
                lastName: "",
                accessLevel: "",
                accessLevelFull: "",
                username: "",
                password: "",
                active: false
            };

            // Reload users
            this.loadUsers();
        },
        // On edit user
        editUser: function() {
            // Define return array
            let returnArray = [];

            // Push items
            returnArray.push(this.selected.id);
            returnArray.push(this.selected.firstName);
            returnArray.push(this.selected.lastName);
            returnArray.push(this.selected.accessLevel);
            returnArray.push(this.selected.username);
            returnArray.push(this.selected.password);

            // Send the array to database
            window.OnEditUser(returnArray);

            // Reload the user view name
            this.viewName = this.selected.firstName + " " + this.selected.lastName;

            // Reload users
            this.loadUsers();
        },
        // Get access level titles from user
        switchAccessLevel: function (i) {
            switch (i) {
                case 0:
                    return "Data Observer";
                case 1:
                    return "Experimenter";
                case 2:
                    return "Administrator";        
            }
        },
        // On create new experiment
        newExperiment: function () {
            // Add new experiment
            window.OnAddNewExperiment(this.experimentCode);

            // Set screens and annul code variable
            this.isNewExperimentOpen = false;
            this.experimentCode = "";
        },
        // Set access level for draft and selected
        setAccessLevel: function(event, level, isSelected = false) {
            if (isSelected) { // Set the selected access level (raw and full)
                this.selected.accessLevel = level;
                this.selected.accessLevelFull = this.switchAccessLevel(level);
            } else { // Set the draft access level (raw and full)
                this.draft.accessLevel = level;
                this.draft.accessLevelFull = this.switchAccessLevel(level);
            }
        },
        // On cancel user
        cancelNewUser: function() {
            // Remove the draft sidebar user
            this.users.shift();

            // Annul draft values
            this.draft = {
                firstName: "",
                lastName: "",
                accessLevel: "",
                accessLevelFull: "",
                username: "",
                password: "",
                active: false
            };

            // Set screens
            this.isNewUserOpen = false;
            this.isNewStart = true;
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
            // Open the search box
            this.isSearchOpen = true;
        },
        // On click away from search bar
        searchHide: function (event) {
            // Get menu & target from DOM
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
        // Open the are you sure menu and pass in the callback
        areYouSureOpen: function (callback) {
            // Set the callback
            this.areYouSureCallback = callback;

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
        // Close the window
        winClose: function () {
            window.OnWindowClose();
        }
    },
    // On create instance
    created () {
        // Add the click listeners for file menu hide and search menu hide
        document.addEventListener('click', this.fileMenuHide);
        document.addEventListener('click', this.searchHide);
    },
    // On destroy instance
    destroyed () {
        // Remove the click listeners for file menu hide and search menu hide
        document.removeEventListener('click', this.fileMenuHide);
        document.removeEventListener('click', this.searchHide);
    }
});