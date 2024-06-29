/* SQL DDLs for Entities and their supporting tables */
    
CREATE TABLE User_ (
    tag VARCHAR(20),
    email VARCHAR(20) NOT NULL,
    passwrd VARCHAR(20) NOT NULL,
    addr_country VARCHAR(20) NOT NULL,
    addr_number INTEGER NOT NULL,
    addr_mailcode CHAR(5) NOT NULL,
    addr_street VARCHAR(20) NOT NULL,
    addr_state VARCHAR(20) NOT NULL,
    addr_city VARCHAR(20) NOT NULL,
    signup_date DATE NOT NULL,
    PRIMARY KEY (tag)
);
    
CREATE TABLE Bird (
    tag VARCHAR(20),
    income DECIMAL(10,2),
    bdate DATE NOT NULL,
    first_name VARCHAR(20) NOT NULL,
    last_name VARCHAR(20) NOT NULL,
    gender ENUM('male', 'female') NOT NULL,
    PRIMARY KEY (tag),
    FOREIGN KEY (tag) REFERENCES User_(tag) ON DELETE CASCADE
);
    
CREATE TABLE Chirp (
    tag VARCHAR(20),
    cno INTEGER,
    parent_tag VARCHAR(20),
    parent_cno INTEGER,
    location_latitude DECIMAL(3,1) NOT NULL,
    location_longitude DECIMAL(4,1) NOT NULL,
    text_ VARCHAR(100) NOT NULL,
    date_ DATE NOT NULL,
    time_ TIME NOT NULL,
    PRIMARY KEY (tag, cno),
    FOREIGN KEY (tag) REFERENCES Bird(tag) ON DELETE CASCADE,
    FOREIGN KEY (parent_tag, parent_cno) REFERENCES Chirp(tag, cno) ON DELETE NO ACTION
);


/* Parrot Statistics View */

CREATE VIEW ParrotStatistics(btag, email, age, num_chirps, min_sentiment, max_sentiment, avg_sentiment, start_date, end_date) AS SELECT B.btag, U.email, TIMESTAMPDIFF(YEAR, B.birthdate, CURRENT_DATE), count(C.btag), MIN(C.sentiment), MAX(C.sentiment), AVG(C.sentiment), MIN(C.date), MAX(C.date) FROM (Bird B JOIN User U ON B.btag = U.tag) LEFT OUTER JOIN Chirp C ON B.btag = C.btag GROUP BY B.btag, U.email
