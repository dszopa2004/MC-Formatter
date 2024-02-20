#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class formatter {
    public:
        int select_val;
        string input_string;
        string substring;
        size_t pos;
        size_t pos_end;
        size_t pos_null;
        vector<string> ingredient;

        void ct_recipe();
        void print_selection();
        void int_selection();
        void ct_print();
        string get_main_name();
        string get_recipe_name();
        bool failsafe(const string&);
        void print_text_invalid();
        void print_text_recipe();
};


/**
 * @brief standard input of ct generated string. 
 * iterates through the string and stores each item within <> and each null to a vector string.
 * 
 */
void formatter::ct_recipe() {
    pos = input_string.find('<');
    pos_null = input_string.find("null");

    while (pos != string::npos || pos_null != string::npos) {
        if (pos_null != string::npos && (pos == string::npos || pos_null < pos)) {
            ingredient.push_back("null");
            pos_null = input_string.find("null", pos_null + 4);
        } else if (pos != string::npos) {
            pos_end = input_string.find('>', pos);
            if (pos_end != string::npos) {
                substring = input_string.substr(pos, pos_end - pos + 1);
                ingredient.push_back(substring);
                pos = input_string.find('<', pos_end);
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
}


/**
 * @brief Get the main name object
 * 
 * @param item_name_main item that the recipe is crafting
 * @param temp stored ingredient 0 string (item being crafted)
 * @return string default name
 */
string formatter::get_main_name() {
    string item_name_main;
    string temp = ingredient[0];
    size_t colon_pos = temp.find(':');
    if (colon_pos == string::npos) {
        return "";
    }

    item_name_main = temp.substr(colon_pos + 1, temp.size() - colon_pos - 2);

    for (size_t i = 0; i < item_name_main.length(); ++i) {
        if (item_name_main[i] == '_') {
            item_name_main[i] = ' ';
        }
    }

    bool capitalize_next = true;
    for (size_t i = 0; i < item_name_main.length(); ++i) {
        if (capitalize_next && islower(item_name_main[i])) {
            item_name_main[i] = toupper(item_name_main[i]);
            capitalize_next = false;
        } else if (isspace(item_name_main[i])) {
            capitalize_next = true;
        }
    }
    return item_name_main;
}


/**
 * @brief Get the recipe name object
 * 
 * @param item_name_recipe item that the recipe is crafting
 * @param temp string to store item thats being crafted (ingredient 0)
 * @return string unique recipe identifier name
 */
string formatter::get_recipe_name() {
    string item_name_recipe;
    string temp = ingredient[0];
    for (size_t i = 1; i < temp.size() - 1; ++i) {
        char ch = temp[i];
        if (ch == ':' || ch == '_') {
            continue;
        }
        item_name_recipe += ch;
    }
    return item_name_recipe;
}


/**
 * @brief prints the formatted string
 * 
 * @param item_name registry name
 * @param item_name_main default name
 * @param item_name_recipe unique recipe identifier name
 * @param ingredient item used in recipe
 */
void formatter::ct_print() {
    cout << "\n<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>\n\n"
         << setfill(' ') << "#" << get_main_name() << "\n"
         << setw(4) << " " << "recipes.remove(" << ingredient[0] << ");\n"
         << setw(4) << " " << "recipes.addShaped(\"" << get_recipe_name() << "\",\n"
         << setw(8) << " " << ingredient[0] << ",\n"
         << setw(12) << " " << "[[" << ingredient[1] << ", " << ingredient[2] << ", " << ingredient[3] << "],\n"
         << setw(12) << " " << "[" << ingredient[4] << ", " << ingredient[5] << ", " << ingredient[6] << "],\n"
         << setw(12) << " " << "[" << ingredient[7] << ", " << ingredient[8] << ", " << ingredient[9] << "]]);\n"
         << "\n<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>\n";
}

/**
 * @brief prints the recipe selection and makes sure the right value is inputed, 
 * otherwise will prompt user again
 * 
 */
void formatter::print_selection() {
    cout << "\n------------------------------\n"
         << "CT Formatter\n"
         << "------------------------------\n"
         << "[1] CT Shaped Table Recipe\n"
         // << "[2] Extended Crafting 3x3\n"
         // << "[3] Extended Crafting 5x5\n"
         // << "[4] Extended Crafting 7x7\n"
         // << "[5] Extended Crafting 9x9\n"
         << "------------------------------\n\n";
}

void formatter::int_selection() {
     while (true) {
        cout << "Select Recipe Type: ";
        if (cin >> select_val && select_val == 1) {
            cin.ignore();
            break;
        } else {
            cin.clear();
            cin.ignore();
            cout << "\n-------- Invalid Input --------\n(Enter a value within the range)\n";
        }
    }
}


/**
 * @brief failsafe for the input string. makes sure the program doesnt shit bricks when someone inputs in the wrong thing
 * 
 * @param input_string standard input string
 * @return true if number of "<" in the input string is at least 6
 * @return false if number of "<" in the input string is less than 6
 */
bool formatter::failsafe(const string& input_string) {
    int count = 0;
    for (char ch : input_string) {
        if (ch == '<') {
            count++;
        }
    }
    return count >= 6;
}

/**
 * @brief prints the invalid input text unpon an invalid input being inputed
 * 
 */
void formatter::print_text_invalid()
{
    cout << "\n----------------------- Invalid Input -----------------------\n";
}

/**
 * @brief prints paste recipe below text
 * 
 */
void formatter::print_text_recipe()
{
    cout << "\nPaste in unformatted recipe below, type 'exit' to end program\n"
         << "v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v\n\n";
}

/**
 * @brief standard input for recipe type selection.
 * 
 */
int main() {
    formatter obj;
    obj.print_selection();
    obj.int_selection();
    
    while (true) {
        obj.print_text_recipe();
        getline(cin, obj.input_string);
        if (obj.input_string == "exit") {
            obj.ingredient.clear();
            break;
        }
        if (obj.failsafe(obj.input_string)) {
            obj.ct_recipe();
            if (obj.ingredient.size() >= 9) {
                obj.ct_print();
                obj.ingredient.clear();
            } else {
                obj.print_text_invalid();
            }
            obj.ingredient.clear();
        } else {
            obj.print_text_invalid();
        }
    }
    return 0;
}