#include <iostream> // Include the standard I/O library for input and output operations
#include <limits> // Include the limits library for handling input validation

using namespace std; // Use the standard namespace to avoid prefixing standard library items

// Constants defining system limitations
const int Maximum_courses = 10; // Maximum number of courses allowed
const int Maximum_students = 5; // Maximum number of students allowed
const int ASSESSMENT = 4; // Number of assessment types per course (Quiz, Mid-term, Project, Final)
const int total_grades_per_course = Maximum_students * ASSESSMENT; // Total grades per course

// Function prototypes for course and grade management
void display_student(string[]); // Function to display the list of students
void display_courses(string[], int); // Function to display the list of courses
void add_course(string[], int&); // Function to add a new course
void remove_course(string[], int&); // Function to remove a course

// Functions for entering grades
void input_grades_per_student_per_course(double[][total_grades_per_course], string[], string[], string[], int); // Input grades for a specific student in a specific course
void input_grades_per_student(double[][total_grades_per_course], string[], string[], string[], int); // Input grades for a specific student across all courses
void input_grades_per_course(double[][total_grades_per_course], string[], string[], string[], int); // Input grades for all students in a specific course

// Functions for calculating averages
void course_average(double[][total_grades_per_course], string[], string[], int); // Calculate the average grade for a specific course
void student_average(double[][total_grades_per_course], string[], string[], int); // Calculate the average grade for a specific student

// Functions for displaying grades
void display_grades_per_course(double[][total_grades_per_course], string[], string[], string[], int); // Display grades for all students in a specific course
void display_grades_per_student(double[][total_grades_per_course], string[], string[], string[], int); // Display grades for a specific student across all courses

// Functions for overall management and validation
void course_management(string[], int&); // Function for course management menu
void grade_entry(double[][total_grades_per_course], string[], string[], string[], int); // Function for grade entry menu
void grade_calculation(double[][total_grades_per_course], string[], string[], int); // Function for grade calculation menu
void grade_lookup(double[][total_grades_per_course], string[], string[], string[], int); // Function for grade lookup menu

void validate_input(); // Function to validate and clear incorrect input

// Main function: Entry point for the program
int main()
{
    cout << "\n******************************************************" << endl; // Print decorative line
    cout << "~~~~~~~~~~~~ A Simple Course Grading System ~~~~~~~~~~\n" << endl; // Print system name

    int choice; // Variable to store user choice in the main menu

    // Initialize the array to store grades for each course
    double course_grades[Maximum_courses][total_grades_per_course] = { {0} }; // Initialize all grades to zero

    // Initialize the list of courses with some initial values
    string courses[Maximum_courses] = {
        "Calculus I",
        "University Physics I",
        "Introduction to Computing",
        "Survey of United Arab Emirates",
        "Linear Algebra",
        "General Chemistry"
    };

    int course_size = 6; // Current number of available courses

    // Initialize the list of students with some initial names
    string students[Maximum_students] = {
        "Jennifer Smith",
        "Michael Johnson",
        "Emily Brown",
        "David Martinez",
        "Sarah Wilson"
    };

    // Define assessment names
    string assessment[ASSESSMENT] = { "Quiz", "Mid_term", "Project", "Final" };

    // Infinite loop to keep the program running until the user chooses to exit
    do
    {
        // Display main menu options
        cout << "Enter your choice(1-5)" << endl;
        cout << "1.Course Management" << endl; // Option to manage courses
        cout << "2.Grade Entry" << endl; // Option to enter grades
        cout << "3.Grade Calculation" << endl; // Option to calculate averages
        cout << "4.Grade Lookup" << endl; // Option to look up grades
        cout << "5.Exit" << endl; // Option to exit
        cout << "Choice: "; // Prompt for user choice
        cin >> choice; // Get the user choice

        validate_input(); // Validate and clear invalid input

        cout << endl; // Print a new line for better readability

        // Switch statement to handle the menu choice
        switch (choice)
        {
        case 1: // If the user chose course management
            course_management(courses, course_size); // Call course management function
            break;

        case 2: // If the user chose grade entry
            grade_entry(course_grades, courses, students, assessment, course_size); // Call grade entry function
            break;

        case 3: // If the user chose grade calculation
            grade_calculation(course_grades, courses, students, course_size); // Call grade calculation function
            break;

        case 4: // If the user chose grade lookup
            grade_lookup(course_grades, courses, students, assessment, course_size); // Call grade lookup function
            break;

        case 5: // If the user chose to exit
            cout << "Exiting program." << endl; // Print exit message
            exit(0);

        default: // If an invalid choice is made
            cout << "Invalid choice. Please choose again from the given alternatives\n" << endl; // Print invalid choice message
            break;
        }

    } while (choice != 5); // Continue the loop until the user chooses to exit

    cout << "******************************************************" << endl; // Print decorative end line

    return 0; // Exit the program
}

// Function to validate input and clear incorrect input from the buffer
void validate_input()
{
    if (cin.fail()) // Check if the input stream is in a failed state
    {
        cin.clear(); // Clear the failure state
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
}

// Function for course management
void course_management(string courses[], int& course_size)
{
    int choice; // Variable to store the user's choice within this submenu
    do
    {
        cout << "Course Management" << endl; // Display submenu title
        cout << "1. Add new courses" << endl; // Option to add new courses
        cout << "2. Remove existing courses" << endl; // Option to remove courses
        cout << "3. Display all available courses" << endl; // Option to display courses
        cout << "4. Back to main menu" << endl; // Option to return to the main menu
        cout << "Choice: "; // Prompt for the user's choice
        cin >> choice; // Get the user's choice

        validate_input(); // Validate and clear invalid input

        cout << endl; // New line for readability

        // Switch statement to handle the submenu choice
        switch (choice)
        {
        case 1: // If the user chose to add a course
            add_course(courses, course_size); // Call the function to add a course
            break;

        case 2: // If the user chose to remove a course
            remove_course(courses, course_size); // Call the function to remove a course
            break;

        case 3: // If the user chose to display courses
            display_courses(courses, course_size); // Call the function to display courses
            break;

        case 4: // If the user chose to return to the main menu
            return; // Exit this submenu

        default: // If an invalid choice is made
            cout << "Invalid choice. Please choose again from the given alternatives\n" << endl; // Error message for invalid choice
            break;
        }
    } while (choice != 4); // Continue the loop until the user chooses to exit this submenu
}

// Function for entering grades
void grade_entry(double course_grades[][total_grades_per_course], string courses[], string students[], string assessment[], int course_size)
{
    int choice; // Variable to store the user's choice within this submenu
    do
    {
        cout << "Grade Entry: " << endl; // Display submenu title
        cout << "1. Input grades per student per course" << endl; // Option to enter grades for a specific student in a course
        cout << "2. Input grades for a student" << endl; // Option to enter grades for a specific student across all courses
        cout << "3. Input grades for a single course" << endl; // Option to enter grades for all students in a specific course
        cout << "4. Back to main menu" << endl; // Option to return to the main menu
        cout << "Choice: "; // Prompt for the user's choice
        cin >> choice; // Get the user's choice

        validate_input(); // Validate and clear invalid input

        cout << endl; // New line for readability

        // Switch statement to handle the submenu choice
        switch (choice)
        {
        case 1: // If the user chose to enter grades for a student in a specific course
            input_grades_per_student_per_course(course_grades, courses, students, assessment, course_size); // Call the function to enter grades for a student in a specific course
            break;

        case 2: // If the user chose to enter grades for a specific student across all courses
            input_grades_per_student(course_grades, courses, students, assessment, course_size); // Call the function to enter grades for a student across all courses
            break;

        case 3: // If the user chose to enter grades for all students in a specific course
            input_grades_per_course(course_grades, courses, students, assessment, course_size); // Call the function to enter grades for all students in a course
            break;

        case 4: // If the user chose to return to the main menu
            return; // Exit this submenu

        default: // If an invalid choice is made
            cout << "Invalid choice. Please choose again from the given alternatives\n" << endl; // Error message for invalid choice
        }
    } while (choice != 4); // Continue the loop until the user chooses to exit this submenu
}

// Function for grade calculation
void grade_calculation(double course_grades[][total_grades_per_course], string courses[], string students[], int course_size)
{
    int choice; // Variable to store the user's choice within this submenu
    do
    {
        cout << "Grade calculation" << endl; // Display submenu title
        cout << "1. Calculate course average" << endl; // Option to calculate course average
        cout << "2. Calculate Average for a student" << endl; // Option to calculate student average
        cout << "3. Back to main menu" << endl; // Option to return to the main menu
        cout << "Choice: "; // Prompt for the user's choice
        cin >> choice; // Get the user's choice

        validate_input(); // Validate and clear invalid input

        cout << endl; // New line for readability

        // Switch statement to handle the submenu choice
        switch (choice)
        {
        case 1: // If the user chose to calculate the course average
            course_average(course_grades, courses, students, course_size); // Call the function to calculate course average
            break;

        case 2: // If the user chose to calculate the student average
            student_average(course_grades, courses, students, course_size); // Call the function to calculate student average
            break;

        case 3: // If the user chose to return to the main menu
            return; // Exit this submenu

        default: // If an invalid choice is made
            cout << "Invalid choice. Please choose again from the given alternatives\n" << endl; // Error message for invalid choice
            break;
        }
    } while (choice != 3); // Continue the loop until the user chooses to exit this submenu
}

// Function for grade lookup
void grade_lookup(double course_grades[][total_grades_per_course], string courses[], string students[], string assessment[], int course_size)
{
    int choice; // Variable to store the user's choice within this submenu
    do
    {
        cout << "Grade Lookup" << endl; // Display submenu title
        cout << "1. Display course grade per student" << endl; // Option to display grades for each student in a course
        cout << "2. Display course grade per course" << endl; // Option to display grades for each course
        cout << "3. Back to main menu" << endl; // Option to return to the main menu
        cout << "Choice: "; // Prompt for the user's choice
        cin >> choice; // Get the user's choice

        validate_input(); // Validate and clear invalid input

        cout << endl; // New line for readability

        // Switch statement to handle the submenu choice
        switch (choice)
        {
        case 1: // If the user chose to display grades for each student in a course
            display_grades_per_student(course_grades, courses, students, assessment, course_size); // Call the function to display grades per student in a course
            break;

        case 2: // If the user chose to display grades for each course
            display_grades_per_course(course_grades, courses, students, assessment, course_size); // Call the function to display grades per course
            break;

        case 3: // If the user chose to return to the main menu
            return; // Exit this submenu

        default: // If an invalid choice is made
            cout << "Invalid choice. Please choose again from the given alternatives\n" << endl; // Error message for invalid choice
            break;
        }
    } while (choice != 3); // Continue the loop until the user chooses to exit this submenu
}

// Function to add a new course
void add_course(string course[], int& course_size)
{
    display_courses(course, course_size); // Display current courses to help user choose

    if (course_size < Maximum_courses) // Check if there is room to add more courses
    {
        cout << "Enter the name of the course you would like to add: "; // Prompt for course name
        getline(cin, course[course_size]); // Use `getline` to read full course name

        cout << course[course_size] << " has been added successfully." << endl; // Confirm course addition
        course_size++; // Increment the course count
    }
    else // If the maximum course limit has been reached
    {
        cout << "Maximum course limit has been reached." << endl; // Display error message
    }
    cout << endl; // New line for readability
}

// Function to remove an existing course
void remove_course(string course[], int& course_size)
{
    display_courses(course, course_size); // Display current courses to help user choose

    int course_num; // Variable to store the course number to remove

    cout << "Enter the course number(1 - " << course_size << "): "; // Prompt for course number
    cin >> course_num; // Get the course number to remove

    validate_input(); // Validate and clear invalid input

    if (course_num <= 0 || course_num > course_size) // Check if the course number is valid
    {
        cout << "\nCourse not in the list!\n"; // Display error message
    }
    else // If the course number is valid
    {
        cout << course[course_num - 1] << " has been successfully removed." << endl; // Confirm course removal

        // Shift the courses to fill the gap created by removing the course
        for (int j = course_num - 1; j < course_size - 1; j++)
        {
            course[j] = course[j + 1]; // Move each course up one index
        }
        course_size--; // Decrement the course count
    }
    cout << endl; // New line for readability
}

// Function to display all available courses
void display_courses(string courses[], int course_size)
{
    if (course_size <= 0) // If no courses are available
    {
        cout << "No courses are available." << endl; // Display error message
        return; // Exit function
    }

    cout << "The available courses are: " << endl; // Display header
    for (int i = 0; i < course_size; i++) // Loop through each course
    {
        cout << i + 1 << ". " << courses[i] << endl; // Print course number and name
    }
    cout << endl; // New line for readability
}

// Function to display all available students
void display_student(string students[])
{
    if (Maximum_students <= 0) // If no students are available
    {
        cout << "No students are available." << endl; // Display error message
        return; // Exit function
    }
    cout << "The available students are: " << endl; // Display header
    for (int i = 0; i < Maximum_students; i++) // Loop through each student
    {
        cout << i + 1 << ". " << students[i] << endl; // Print student number and name
    }
    cout << endl; // New line for readability
}

// Function to input grades for a specific student in a specific course
void input_grades_per_student_per_course(double course_grades[][total_grades_per_course], string courses[], string students[], string assessment[], int course_size)
{
    display_courses(courses, course_size); // Display current courses to help user choose

    int course_num; // Variable to store the course number

    cout << "Enter the course number(1 - " << course_size << "): "; // Prompt for course number
    cin >> course_num; // Get the course number

    validate_input(); // Validate and clear invalid input

    if (course_num <= 0 || course_num > course_size) // If the course number is invalid
    {
        cout << "Course not found" << endl; // Display error message
        cout << endl; // New line for readability
        return; // Exit function
    }

    int student_num; // Variable to store the student number

    display_student(students); // Display current students to help user choose

    cout << "Enter the student number(1 - 10): "; // Prompt for student number
    cin >> student_num; // Get the student number

    validate_input(); // Validate and clear invalid input

    if (student_num <= 0 || student_num > 10) // If the student number is invalid
    {
        cout << "Student not found" << endl; // Display error message
        cout << endl; // New line for readability
        return; // Exit function
    }

    // Record grades for the specified student in the specified course
    cout << "Enter the grades for " << students[student_num - 1] << " in " << courses[course_num - 1] << ": " << endl; // Prompt for grades
    for (int i = 0; i < ASSESSMENT; i++) // Loop through each assessment type
    {
        cout << assessment[i] << ": "; // Display the assessment type
        cin >> course_grades[course_num - 1][student_num * ASSESSMENT - i]; // Record the grade for the specific assessment
        validate_input(); // Validate and clear invalid input
    }
    cout << 4 << " grades are recorded for " << students[student_num - 1] << " in " << courses[course_num - 1] << endl; // Confirm that grades were recorded

    cout << endl; // New line for readability
}

// Function to input grades for a specific student across all courses
void input_grades_per_student(double course_grades[][total_grades_per_course], string courses[], string students[], string assessment[], int course_size)
{
    display_student(students); // Display current students to help user choose

    int student_num; // Variable to store the student number

    cout << "Enter the student position in number(1 - 10): "; // Prompt for student number
    cin >> student_num; // Get the student number

    validate_input(); // Validate and clear invalid input

    if (student_num <= 0 || student_num > 10) // If the student number is invalid
        return; // Exit function

    // Record grades for the specified student across all courses
    for (int i = 0; i < course_size; i++) // Loop through each course
    {
        cout << "Enter the grade for " << students[student_num - 1] << " in " << courses[i] << ": " << endl; // Prompt for grades in the course
        for (int j = 0; j < 4; j++) // Loop through each assessment type
        {
            cout << assessment[j] << ": "; // Display the assessment type
            cin >> course_grades[i][(student_num - 1) * ASSESSMENT + j]; // Record the grade
            validate_input(); // Validate and clear invalid input
        }
        cout << endl; // New line for readability
    }
    cout << "All the grades for " << students[student_num - 1] << " have been entered successfully." << endl; // Confirm that grades were recorded
    cout << endl; // New line for readability
}

// Function to input grades for all students in a specific course
void input_grades_per_course(double course_grades[][total_grades_per_course], string courses[], string students[], string assessment[], int course_size)
{
    display_courses(courses, course_size); // Display current courses to help user choose

    int course_num; // Variable to store the course number

    cout << "Enter the course number(1 - " << course_size << "): "; // Prompt for course number
    cin >> course_num; // Get the course number

    validate_input(); // Validate and clear invalid input

    if (course_num <= 0 || course_num >= 11) // If the course number is invalid
        return; // Exit function

    cout << endl; // New line for readability

    // Record grades for all students in the specified course
    for (int i = 0; i < Maximum_students; i++) // Loop through each student
    {
        cout << "Enter the grade for " << students[i] << " in " << courses[course_num - 1] << ": " << endl; // Prompt for grades for each student in this course
        for (int j = 0; j < 4; j++) // Loop through each assessment type
        {
            cout << assessment[j] << ": "; // Display the assessment type
            cin >> course_grades[course_num - 1][i * ASSESSMENT + j]; // Record the grade
            validate_input(); // Validate and clear invalid input
        }
        cout << endl; // New line for readability
    }
    cout << "All the grades for " << courses[course_num - 1] << " have been entered successfully." << endl; // Confirm that grades were recorded
    cout << endl; // New line for readability
}

// Function to calculate the average grade for a specific course
void course_average(double course_grades[][total_grades_per_course], string courses[], string students[], int course_size)
{
    display_courses(courses, course_size); // Display current courses to help user choose

    int course_num; // Variable to store the course number

    cout << "Enter the course number(1 - " << course_size << "): "; // Prompt for course number
    cin >> course_num; // Get the course number

    validate_input(); // Validate and clear invalid input

    double total_grade = 0; // Variable to store the total grade for the course

    if (course_num > 0 && course_num <= 10) // Check if the course number is valid
    {
        // Loop through each student to calculate the total grade for this course
        for (int j = 0; j < Maximum_students; j++)
        {
            double student_grade = 0; // Variable to store the grade for each student
            for (int k = 0; k < ASSESSMENT; k++) // Loop through each assessment type
            {
                student_grade += course_grades[course_num - 1][j * ASSESSMENT + k]; // Add the grade for the specific assessment
            }
            total_grade += student_grade; // Add the student's grade to the total
        }

        cout << "\nThe Average grade for " << courses[course_num - 1] << " is: "; // Display the average for the course
        cout << (double)total_grade / (double)Maximum_students << endl; // Calculate the course average
        cout << endl; // New line for readability
    }
}

// Function to calculate the average grade for a specific student across all courses
void student_average(double course_grades[][total_grades_per_course], string courses[], string students[], int course_size)
{
    display_student(students); // Display current students to help user choose

    int student_num; // Variable to store the student number

    cout << "Enter the course number (1 - 10): "; // Prompt for student number
    cin >> student_num; // Get the student number

    validate_input(); // Validate and clear invalid input

    if (student_num <= 0 || student_num > 10) // If the student number is invalid
        return; // Exit function

    double total_grade = 0; // Variable to store the total grade for the student

    // Loop through each course to calculate the total grade for this student
    for (int j = 0; j < course_size; j++)
    {
        double student_grade = 0; // Variable to store the grade for each course
        for (int k = 0; k < ASSESSMENT; k++) // Loop through each assessment type
        {
            student_grade += course_grades[j][(student_num - 1) * ASSESSMENT + k]; // Add the grade for each assessment
        }
        total_grade += student_grade; // Add the course grade to the total
    }

    cout << "The Average grade for " << students[student_num - 1] << " is: "; // Display the average for the student
    cout << (double)total_grade / (double)course_size << endl; // Calculate the student average
    cout << endl; // New line for readability
}

// Function to display grades for each student in a specific course
void display_grades_per_course(double course_grades[][total_grades_per_course], string courses[], string students[], string assessment[], int course_size)
{
    display_courses(courses, course_size); // Display current courses to help user choose

    int course_num; // Variable to store the course number

    cout << "Enter the course number(1 - " << course_size << "): "; // Prompt for course number
    cin >> course_num; // Get the course number

    validate_input(); // Validate and clear invalid input

    if (course_num <= 0 || course_num > 10) // If the course number is invalid
    {
        cout << "Invalid choice!"; // Display error message
        return; // Exit function
    }

    cout << "Grades for " << courses[course_num - 1] << ": " << endl; // Display course header
    for (int i = 0; i < Maximum_students; i++) // Loop through each student
    {
        cout << students[i] << " : \n"; // Display student name
        for (int j = 0; j < 4; j++) // Loop through each assessment type
        {
            cout << "\t" << assessment[j] << " = " << course_grades[course_num - 1][i * ASSESSMENT + j] << endl; // Display the grade for the specific assessment
        }
        cout << endl; // New line for readability
    }
    cout << endl; // New line for readability
}

// Function to display grades for each course for a specific student
void display_grades_per_student(double course_grades[][total_grades_per_course], string courses[], string students[], string assessment[], int course_size)
{
    display_student(students); // Display current students to help user choose

    int student_num; // Variable to store the student number

    cout << "Enter the student number(1 - 5): "; // Prompt for student number
    cin >> student_num; // Get the student number

    validate_input(); // Validate and clear invalid input

    if (student_num <= 0 || student_num > 5) // If the student number is invalid
        return; // Exit function

    cout << "Grades for " << students[student_num - 1] << ": \n\n"; // Display student header
    for (int i = 0; i < course_size; i++) // Loop through each course
    {
        cout << courses[i] << " : \n"; // Display course name
        for (int j = 0; j < 4; j++) // Loop through each assessment type
        {
            cout << "\t" << assessment[j] << " = " << course_grades[i][(student_num - 1) * ASSESSMENT + j] << endl; // Display the grade for each assessment
        }
        cout << endl; // New line for readability
    }
    cout << endl; // New line for readability
}
