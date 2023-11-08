#!/bin/bash

ADDRESS_BOOK="address_book.txt"

# Function to create a new address book 
create_address_book() {
  if [ -f "$ADDRESS_BOOK" ]; then
    read -p "Address book file already exists. Do you want to overwrite it? (y/n): " choice
    if [ "$choice" == 'y' ]; then
      >"$ADDRESS_BOOK"
      echo "Creating a new address book..."
    else
      echo "Keeping the existing address book."
    fi
  else
    echo "Creating a new address book..."
    touch "$ADDRESS_BOOK"
  fi
}

# Function to display an address book 
display_record() {
    if [ -s "$ADDRESS_BOOK" ]; then
        # Use awk to format the data into columns
        awk -F: 'BEGIN { printf "%-20s %-20s %-20s %-20s \n", "HouseNo", "Name", "Address", "Phone Number";
        printf "---------------------------------------------------------------------------------------\n" }
        { printf "%-20s %-20s %-20s %-20s \n", $1, $2, $3, $4 }' "$ADDRESS_BOOK"
    else
        echo "Address book is empty."
    fi
}

# Function to insert records to address book 
insert_record() {
    read -p "Enter the name: " name
    read -p "Enter the address: " address
    read -p "Enter the house no: " house

    # Validate phone number input
    while true; do
        read -p "Enter the Phone number (10 digits only): " phn
        if [[ ! $phn =~ ^[0-9]{10}$ ]]; then
            echo "Invalid phone number format. Please enter a 10-digit phone number."
        else
            break
        fi
    done

    echo "$house:$name:$address:$phn" >> "$ADDRESS_BOOK"
    echo "Record inserted successfully."
}

# Function to delete a record from the address book
delete_record() {
    read -p "Enter house No to delete: " house
    # Use grep to check if the name exists in the address book file
    if grep -q "^$house:" "$ADDRESS_BOOK"; then
        # If the name exists, delete the record and create a temporary file
        grep -v -i "^$house:" "$ADDRESS_BOOK" > temp.txt
        # Move the temporary file to the original address book file
        mv temp.txt "$ADDRESS_BOOK"
        echo "Record of $house deleted successfully."
    else
        # If the name doesn't exist, show the record not found message
        echo "Record not found."
    fi
}

# Function to modify an address book 
modify_record() {
    echo "Enter the house no to modify:"
    read house

    if grep -q "^$house:" "$ADDRESS_BOOK"; then
        while true; do
            echo "Options:"
            echo "1) Modify address? "
            echo "2) Modify Phone?"
            echo "3) Modify Name?"
            echo "4) Done with Modifying?"
            echo "Enter your choice:"
            read choice

            case "$choice" in
                1)  echo "Enter the new address:"
                    read new_address
                    # Update the address variable
                    address="$new_address"
                    sed -i "s/^$house:.*/$house:$name:$address:$phn/" "$ADDRESS_BOOK"
                    echo "Record modified successfully." ;;
                2)  echo "Enter the new Phone Number:"
                    read new_phn
                    # Update the phn variable
                    phn="$new_phn"
                    sed -i "s/^$house:.*/$house:$name:$address:$phn/" "$ADDRESS_BOOK"
                    echo "Record modified successfully.";;
                3)  echo "Enter the new Name:"
                    read new_name
                    # Update the name variable
                    name="$new_name"
                    sed -i "s/^$house:.*/$house:$name:$address:$phn/" "$ADDRESS_BOOK"
                    echo "Record modified successfully.";;
                4) break ;;
                *) echo "Invalid choice. Please try again." ;;
            esac
        done
    else
        echo "House no not found in the address book."
    fi

}

while true; do
    echo "Options:"
    echo "1) Create address book"
    echo "2) Display address book"
    echo "3) Insert a record"
    echo "4) Delete a record"
    echo "5) Modify a record"
    echo "6) Exit"

    read -p "Enter your choice: " choice

    case "$choice" in
        1) create_address_book ;;
        2) display_record ;;
        3) insert_record ;;
        4) delete_record ;;
        5) modify_record ;;
        6) echo "Exiting address book program..." ; break ;;
        *) echo "Invalid choice. Please try again." ;;
    esac
done