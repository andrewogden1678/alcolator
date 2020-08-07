// Record component
var ComponentUser = Vue.component('user', {
    props: ["user"],
    template: '<div class="flexbox-row--align margin--dataitem dataitem" style="min-height: 73px;"><i class="material-icons list-icon" style="width: 20%; margin-right: 20px; margin-left: 5px">assignment_ind</i><div class="flexbox-column--align"><div class="flexbox-row--alignleft"><h5 class="nomargin" style="text-align: left; font-size: 14pt;">{{user.firstName}} {{user.lastName}}</h5></div><div class="flexbox-row--alignleft"><h3 class="nomargin" style="text-align: left;">{{user.accessLevelFull}}</h3></div></div></div>'
});

// Dropdown component
var ComponentDropdown = Vue.component('dropdown', {
    props: ["obj"],
    template: '<h6 class="dropdown-option">{{obj}}</h6>'
});

// Vue instance
let vm = new Vue({
    el: '#vm', // container ID 
    data: {
        users: [ // Array of users

        ],
        searchUsers: [

        ],
        experiments: [

        ],
        accessLevels: {
            observer: "Data Observer",
            experimenter: "Experimenter",
            administrator: "Administrator"
        },
        user: { // Current user in session
            id: null,
            firstName: "",
            lastName: "",
            accessLevel: "",
        }, 
        draft: {
            firstName: "",
            lastName: "",
            accessLevel: "",
            accessLevelFull: "",
            username: "",
            password: "",
            active: false
        },
        selected: {
            
        },
        viewName: "", // Display name when viewing subject
        searchText: "", // Text for search
        isNewStart: true, // Program just started
        isFileMenuOpen: false, // File menu open
        isNewUserOpen: false, // New user open
        isViewingUser: false, // Is viewing a user
        isSearchOpen: false, // Check if search is open
        isSearchActive: false // Check if currently typing
        
    },
    components: {
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
                let users = this.users.filter(u => u.firstName.includes(this.searchText) || u.lastName.includes(this.searchText));

                // Loop through found users and push
                for (i = 0; i < users.length; i++) {
                    this.searchUsers.push(users[i]);
                }
            }
        }
    },
    methods: {
        initialLoad: function () {
            // TODO: Get user
            
            // Get users
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

            // Get experiments
            let exps = window.OnLoadExperiments();
            for (i = 0; i < exps.length; i++) {
                this.experiments.push({
                    id: exps[i][0], 
                    name: exps[i][1]
                });
            }
        },
        loadUsers: function () {
            // Empty array
            this.users = [];
            // Get users
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
            this.isNewUserOpen = true;
        },
        fileNewExp: function () {

        },
        fileExpMode: function () {
            window.OnClickExperimenterMode(userId)
        },
        fileLogOut: function () {
            window.OnLogOut();
        },
        /// User methods
        userClick: function (event, user) {
            // Reset selected
            this.resetSelected();
            
            // Check if draft is active
            if (user.draft) {
                // Reset screen
                this.isViewingUser = false;
                this.isNewUserOpen = true;
            } else {
                // If user is admin
                if (user.accessLevel == 2) {
                    this.isSelectedAdmin = true;
                } else {
                    this.isSelectedAdmin = false;
                }
                // Assign user to the selected
                this.selected = {
                    id: user.id,
                    firstName: user.firstName,
                    lastName: user.lastName,
                    accessLevel: user.accessLevel,
                    accessLevelFull: user.accessLevelFull,
                    username: user.username,
                }
                
                // Assign display name
                this.viewName = user.firstName + " " + user.lastName;

                // Set screens
                this.isViewingUser = true;
                this.isNewStart = false;
                this.isNewUserOpen = false;
            }
        },
        resetSelected: function () {
            // Reset selected
            this.selected = {
                subject_code: ""
            };
        },
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

            // Send the array
            window.OnSaveUser(returnArray);

            // Deactivate draft
            this.selected.draft = false;

            // Set screens
            this.isNewUserOpen = false;
            this.isViewingUser = true;

            // Set selected
            this.selected = Object.assign({}, this.draft);
            this.viewName = this.draft.firstName + " " + this.draft.lastName;

            // Reset draft
            // Reset draft
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
        editUser: function() {
            // TODO: UPDATED SUCCESSFULLY BANNER
            // Define return array
            let returnArray = [];

            // Push items
            returnArray.push(this.selected.id);
            returnArray.push(this.selected.firstName);
            returnArray.push(this.selected.lastName);
            returnArray.push(this.selected.accessLevel);
            returnArray.push(this.selected.username);

            // Send the array
            window.OnEditUser(returnArray);

            // Reload the name
            this.viewName = this.selected.firstName + " " + this.selected.lastName;

            // Reload users
            this.loadUsers();
        },
        deleteUser: function() {
            // Send delete query
            // TODO: ARE YOU SURE GATE
            window.OnDeleteUser(this.selected.id); 

            // Set screens
            this.isViewingUser = false;
            this.isNewStart = true;

            // Reload users
            this.loadUsers();
        },
        switchAccessLevel: function (i) { // Get the titles
            switch (i) {
                case 0:
                    return "Data Observer";
                case 1:
                    return "Experimenter";
                case 2:
                    return "Administrator";        
            }
        },
        setAccessLevel: function(event, level, isSelected = false) {
            if (isSelected) { // Set the selected access level (raw and full)
                this.selected.accessLevel = level;
                this.selected.accessLevelFull = this.switchAccessLevel(level);
            } else { // Set the draft access level (raw and full)
                this.draft.accessLevel = level;
                this.draft.accessLevelFull = this.switchAccessLevel(level);
            }
        },
        cancelNewUser: function() {
            // Remove the draft sidebar user
            this.users.shift();

            // Reset draft
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
        /// Window methods
        winClose: function () {
            // TODO: ARE YOU SURE WINDOW
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