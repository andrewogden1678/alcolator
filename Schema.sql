create table identities(id integer PRIMARY KEY, 
                        first_name varchar not NULL, 
                        last_name varchar NOT NULL, 
                        access_level tinyint NOT NULL, 
                        username varchar NOT NULL, 
                        password VARCHAR NOT NULL);
                        
create table experiments(id integer primary key, 
                         name varchar NOT NULL, 
                         is_concluded integer NOT NULL);

Create TABLE beverages(id integer primary key, 
                       name varchar NOT NULL, 
                       concentration decimal NOT NULL);
                       
Create TABLE action_logs(id integer primary key, 
                       identity_id integer NOT NULL, 
                       message varchar NOT NULL,
                       created_on datetime not NULL,
                       FOREIGN key (identity_id) 
                      		 REFERENCES identities (id));                       

create table subjects(id integer primary key, 
                      subject_code varchar NOT NULL, 
                      experimenter_id integer NOT NULL,
                      experiment_id integer NOT NULL,
                      age integer NOT NULL,
                      gender integer NOT NULL,
                      height integer NOT NULL,
                      weight integer NOT NULL,
                      created_on datetime NOT NULL,
                      FOREIGN key (experimenter_id) 
                      		REFERENCES identities (id),
                      FOREIGN key (experiment_id) 
                      		REFERENCES experiments (id));
                      
create table results(id integer primary key, 
                     subject_id integer not NULL,
                     beverage_id integer NOT NULL,
                     target_bac decimal NOT NULL,
                     target_bac_time int NOT NULL,
                     amount_grams decimal NOT NULL,
                     amount_beverage DECIMAL NOT NULL,
                     actual_bac DECIMAL,
                     actual_bac_time Datetime,
                     FOREIGN key (subject_id) 
                      		REFERENCES identities (id),
                     FOREIGN key (beverage_id) 
                      		REFERENCES beverages (id));