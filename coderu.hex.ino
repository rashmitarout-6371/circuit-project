
#include <LiquidCrystal.h> //library for LCD 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// defines pins numbers
const int Relay_Pin = 7;

// Weekly schedule for each day
const char* daysOfWeek[6] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

struct Class {
  const char* time;
  const char* subject;
  const char* teacher;
};

   
Class schedule[6][8] = {
  { // Monday
    {"8:30-9:30", "LUNCH", "Break        "},
    {"9:30-10:30", "IOT", "Vikash sir    "},
    {"10:30-11:30", "Gr.Tech", "Alok sir "},
    {"2:00-4:00", "Seminar","Saumendrasir"}
  },
  { // Tuesday
    {"8:30-9:30",  "IOT", "Vikash sir     "},
    {"9:30-12:30",  "EET", "Sudeshna mam  "},
    {"12:30-1:00",  "Lunch", "Break       "},
    {"1:00-2:00",  "DIP", "Monalisha mam  "},
    {"2:00-4:00", "Minor.pro.","Priyajitsir"},
    {"", "", ""}, // Placeholder for unused slots
    {"", "", ""}
  },
  { // Wednesday
    {"8:30-9:30", "SC", "Subhendu sir    "},
    {"9:30-10:30", "IOT", "Vikash sir    "},
    {"10:30-11:30", "DIP", "Monalisa mam "},
    {"11:30-12:30", "ED", "Angurubala mam"},
    {"12:30-1:00", "Lunch", "Break       "},
    {"1:00-2:00", "Gr.Tech", "Alok sir   "},
    {"2:00-3:00", "IVP", "Debi sir       "},
    {"3:00-4:00", "SC", "Subhendu sir"}
  },
  { // Thursday
    {"8:30-9:30", "ED", "Angurubala mam  "},
    {"9:30-10:30", "Gr.Tech", "Alok sir  "},
    {"10:30-11:30", "DIP", "Monalisha mam"},
    {"11:30-12:30", "SC", "Subhendu sir  "},
    {"12:30-1:00", "Lunch", "Break       "},
    {"1:00-2:00", "IVP", "Debi sir       "},
    {"2:00-4:00", "HOBBY", "STU.         "},
    {"", "", ""}
  },
  { // Friday
    {"8:30-9:30", "ED", "Angurubala mam "},
    {"9:30-10:30", "DIP", "Monalisha mam"},
    {"10:30-11:30", "Lunch", "Break     "},
    {"11:30-12:30", "SC", "Subhendu sir "},
    {"12:30-1:00", "Lunch", "Break      "},
    {"1:00-2:00", "Gr.Tech", "Alok sir  "},
    {"2:00-3:00","EET TECH","Priyajitsir"},
    {"3:00-4:00", "IVP", "Debi sir      "}
  },
  { // Saturday
    {"8:30-9:30", "IOT", "Vikash sir    "},
    {"9:30-10:30", "ED", "Angurubala mam"},
    {"10:30-11:30", "DIP","Monalisha mam"},
    {"11:30-12:30", "SC", "Subhendu sir "},
    {"12:30-1:00", "Lunch", "Break      "},
    {"1:00-2:00", "EIKT", "Pranati mam  "},
    {"2:00-3:00", "IVP", "Debi sir      "},
    {"3:00-4:00", "Gr.Tech", "Alok sir  "}
  }
};

void ringBell(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(Relay_Pin, HIGH);
    delay(1000);
    digitalWrite(Relay_Pin, LOW);
    delay(1000);
  }
}

void displayClass(int day, int classIndex) {
  lcd.setCursor(0, 3);
  lcd.print("CLASS: ");
  lcd.print(classIndex + 1);
  lcd.print(" ");
  lcd.print(schedule[day][classIndex].time);
  lcd.setCursor(0, 2);
  lcd.print(schedule[day][classIndex].subject);
  lcd.print(" - ");
  lcd.print(schedule[day][classIndex].teacher);
  delay(5000);
}

void setup() {
  pinMode(Relay_Pin, OUTPUT); // Sets the Pin as an Output
  
  lcd.begin(20, 4); //LCD order: set up the LCD's number of columns and rows:
  // Prints the initial message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("   THE BRIGHT LIGHT   ");
  lcd.setCursor(0, 1);
  lcd.print(" AUTO BELLING SYSTEM       ");
  delay(1000);

  for (int currentDay = 0; currentDay < 6; currentDay++) {
    // Display the day and start message
    lcd.setCursor(0, 2);
    lcd.print("    ");
    lcd.print(daysOfWeek[currentDay]);
    lcd.print("   ");
    lcd.setCursor(0, 3);
    lcd.print(" CLASS TIME STARTED      ");
    ringBell(4);
    delay(1000);

    // Display each class and ring bell at start of each class
    for (int i = 0; i < 8; i++) {
      if (schedule[currentDay][i].time[0] == '\0') break; // Skip empty slots
      ringBell(1);
      displayClass(currentDay, i);
    }

    // End of the day message
    lcd.setCursor(0, 2);
    lcd.print("  CLASS   CLOSED          ");
    lcd.setCursor(0, 3);
    lcd.print(" COLLEGE TIME CLOSED      ");
    ringBell(4);
    digitalWrite(Relay_Pin, HIGH);
    delay(1000);
    digitalWrite(Relay_Pin, LOW);

    // Delay before moving to the next day
    delay(1000);
  }
}

void loop() {
  // This loop function is necessary but should remain empty because all logic is implemented in setup().
}
