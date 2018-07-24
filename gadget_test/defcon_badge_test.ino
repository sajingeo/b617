#include <Wire.h>
#define BADGES_KNOWN     (6)

uint8_t list_of_badge[16]={0};
uint8_t number_of_badge_found=0;

bool disable_scan = false;

char* known_badge_names[BADGES_KNOWN]={
  "AND!XOR",
  "AND!XOR",
  "MR ROBOT",
  "MR ROBOT",
  "MR BLINK BLING",
  "DC617"
};

uint8_t know_address[BADGES_KNOWN]={
  0x30,0x18,0x60,0xA0,0x42,0x26
};


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  print_menu();
}

static print_menu()
{
  Serial.println("Starting shitty defcon badge sniffer...");
  Serial.println("1.scan for all address [Default]");
  Serial.println("2.wite to address <addre(dec),data<CR>>");
  Serial.println("3.enable continuous scan");
  Serial.println("==== send s to stop scanning ====");
}

static uint8_t lookup_badge_id(uint8_t address)
{
  for(int i =0 ; i < BADGES_KNOWN ; i++)
  {
    if (know_address[i] == address)
        {return i;}
  }
}

static void search_for_badges()
{
  byte error, address;
  int nDevices;
  int badge_index = 0;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      badge_index = lookup_badge_id(address);
      
      Serial.print("Found ");
      Serial.print(known_badge_names[badge_index]);
      Serial.print(" badge at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      
      list_of_badge[number_of_badge_found]=address;
      number_of_badge_found++;
      
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No DC26 badges found :(\n");
  else
    Serial.println("done...\n");

 
  delay(5000);           // wait 5 seconds for next scan
}

static void write_to_badge()
{
  Serial.println("Sending FFs to all badges!!");
  for(int i=0; i<number_of_badge_found ;i++)
  {
    Wire.beginTransmission(list_of_badge[i]);
    Wire.write(0xFF);
    Wire.endTransmission();
  }
}

static void read_from_badge()
{
  Serial.println("Reading data from all badges!!");
  for(int i=0; i<number_of_badge_found ;i++)
  {
    Wire.requestFrom((uint8_t)list_of_badge[i],(uint8_t)255);
    while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    if(( c > 31 )&&(c < 127)) // check for valid ascii
    {
      Serial.print(c);         // print the character
    }
  }
  Serial.println("\n--- End of Tx ---");
  }
}

static void try_to_talk_badge()
{
  //try to write FF to the badge
  write_to_badge();

  //try to read data from the badge
  read_from_badge();
}

static void print_list()
{
  for(int i=0; i<number_of_badge_found ;i++)
  {
  Serial.print("LOC:");
  Serial.print(i,DEC);
  Serial.print("ADDR:");
  Serial.print(list_of_badge[i],HEX);
  Serial.print("\n");
  }
}

void loop() {
  while(1)
  {
    memset(list_of_badge,0,sizeof(list_of_badge));
    number_of_badge_found = 0;
    
    if (Serial.available() > 0) {
      uint8_t menu_selection = Serial.read();

      switch (menu_selection){
      
      case'1':
          search_for_badges();
          break;  
      
      case '2':
        Serial.println("Not supported yet!!");
        break;

      case '3':
        Serial.println("Cont. scanning enabled!!");
        disable_scan = false;
        break;

      case 's':
        Serial.println("stopping scan!!");
        disable_scan = true;
        break;

      case '\n':
        break;

      case '\r':
        break;

      default:
        print_menu();
        break;
      }
    }
    else{
      delay(5000);
      if (! disable_scan)
      {
        search_for_badges();
      }
    }

    if (number_of_badge_found > 0)
    {
//      to debug list
//      print_list();
      try_to_talk_badge();
    }
  }
}



