#!/bin/bash

ADDRESS_BOOK="address_book.txt"

# Function to create a new address book file
create_address_book() {
  if [ -f "$ADDRESS_BOOK" ]; then
    read -p "Address book file already exists. Do you want to overwrite it? (y/n): " choice
    if [ "$choice" == "y" ]; then
      echo "Creating a new address book..."
      > "$ADDRESS_BOOK"
    else
      echo -e "\nKeeping the existing address book."
    fi
  else
    echo -e "\nCreating a new address book..."
    touch "$ADDRESS_BOOK"
  fi
}

# Function to insert a new record to the address book
insert_record() {
  read -p "Name: " name
  read -p "City: " city
  read -p "Phone: " phone

  # Append the record to the address book file
  echo "$name  $city $phone" >> "$ADDRESS_BOOK"
  echo -e "\nRecord inserted successfully!"
}

# Function to display records from the address book
display_record(){
	echo "Records in Address book are..."
	cat "$ADDRESS_BOOK"
}

# Function to delete a record from the address book
delete_record(){
	
	read -p "Enter the name of the record you want to delete: " name
    if grep -q -i -w "$name" "$ADDRESS_BOOK"; then
        grep -v -i -w "$name" "$ADDRESS_BOOK" > temp.txt
        mv temp.txt "$ADDRESS_BOOK"
        echo "Record deleted successfully!"
    else
        echo "Record not found."
    fi

}

# Function to update a record in the address book
update_record(){
	  read -p "Enter the name of the record you want to modify: " name

if grep -q -i -w "^$name:" "$ADDRESS_BOOK"; then
  while true; do
    echo "Options:"
    echo "1) Modify city? "
    echo "2) Modify Phone?"
    echo "3) Done with Modifying?"
    read -p "Enter your choice: " choice

    case "$choice" in
      1)
        echo "Enter the new city:"
        read new_city
        # sed is stream editor which replace new value over existing value
        sed -i "s/^$name:[^:]*:/$name:$new_city:/" "$ADDRESS_BOOK"
        echo "Record modified successfully." ;;
      2)
        echo "Enter the new PhoneNo:"
        read new_phone
        # sed is stream editor which replace new value over existing value
        sed -i "s/^$name:[^:]*:$name:[^:]*/$name:$new_phone/" "$ADDRESS_BOOK"
        echo "Record modified successfully." ;;
      3)
        break ;;
      *)
        echo "Invalid choice. Please try again." ;;
    esac
  done

else
  echo "Record not found."
fi

}



while true 
do
  echo -e "\nAddress Book Menu:"
  echo "1. Create a new address book"
  echo "2. Insert a new record"
  echo "3. Display a record"
  echo "4. Delete a record"
  echo "5. Update a record"
  echo "6. Exit"
  read -p "Enter your choice: " choice

  case $choice in
    1) create_address_book ;;
    2) insert_record ;;
    3) display_record ;;
    4) delete_record ;;
    5) update_record ;;
    6) echo "Goodbye!"; exit 0 ;;
    *) echo "Invalid choice. Please try again." ;;
  esac
done