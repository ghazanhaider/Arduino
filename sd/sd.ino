
    #include <SPI.h>
    #include <SD.h>
 
    // set up variables using the SD utility library functions:
    Sd2Card card;
    SdVolume volume;
    SdFile root;
 
    const int chipSelect = 5;
 
    void setup()
    {
      // Open serial communications and wait for port to open:
      Serial.begin(9600);
      while (!Serial) {
      }
 
 
      Serial.print("\nInitializing SD card...");
      pinMode(53, OUTPUT);     // change this to 53 on a mega
 
 
      // we'll use the initialization code from the utility libraries
      // since we're just testing if the card is working!
      if (!card.init(SPI_HALF_SPEED, chipSelect)) {
        Serial.println("initialization failed. Things to check:");
        Serial.println("* is a card is inserted?");
        Serial.println("* Is your wiring correct?");
        Serial.println("* did you change the chipSelect pin to match your shield or module?");
        return;
      } else {
        Serial.println("Wiring is correct and a card is present.");
      }
 
      // print the type of card
      Serial.print("\nCard type: ");
      switch (card.type()) {
        case SD_CARD_TYPE_SD1:
          Serial.println("SD1");
          break;
        case SD_CARD_TYPE_SD2:
          Serial.println("SD2");
          break;
        case SD_CARD_TYPE_SDHC:
          Serial.println("SDHC");
          break;
        default:
          Serial.println("Unknown");
      }
 
      // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
      if (!volume.init(card)) {
        Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
        return;
      }
 
 
      // print the type and size of the first FAT-type volume
 
      uint64_t volumesize64;
      uint32_t volumesize32;
      Serial.print("\nVolume type is FAT");
      Serial.println(volume.fatType(), DEC);
      Serial.println();
 
      volumesize64 = volume.blocksPerCluster();    // clusters are collections of blocks
      volumesize64 *= volume.clusterCount();       // we'll have a lot of clusters
      volumesize64 *= 512;                            // SD card blocks are always 512 bytes
 
      Serial.print("Volume size (bytes): ");
      printLLNumber(volumesize64, DEC);
      Serial.println();
 
      Serial.print("Volume size (Kbytes): ");
      volumesize32 = volumesize64/1024;
      Serial.println(volumesize32);
 
      Serial.print("Volume size (Mbytes): ");
      volumesize32 /= 1024;
      Serial.println(volumesize32);
      /*uint64_t volumesize;
      Serial.print("\nVolume type is FAT");
      Serial.println(volume.fatType(), DEC);
      Serial.println();
 
      volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
      volumesize *= volume.clusterCount();       // we'll have a lot of clusters
      volumesize *= 512;                            // SD card blocks are always 512 bytes
      Serial.print("Volume size (bytes): ");
      Serial.println(volumesize,DEC);
      Serial.print("Volume size (Kbytes): ");
      volumesize /= 1024;
      Serial.println(volumesize,DEC);
      Serial.print("Volume size (Mbytes): ");
      volumesize /= 1024;
      Serial.println(volumesize,DEC);
    */
 
      Serial.println("\nFiles found on the card (name, date and size in bytes): ");
      root.openRoot(volume);
 
      // list all files in the card with date and size
      root.ls(LS_R | LS_DATE | LS_SIZE);
    }
 
 
    void loop(void) {
 
    }
    void printLLNumber(uint64_t n, uint8_t base)
    {
      unsigned char buf[16 * sizeof(long)];
      unsigned int i = 0;
 
      if (n == 0)
      {
        Serial.print((char)'0');
        return;
      }
 
      while (n > 0)
      {
        buf[i++] = n % base;
        n /= base;
      }
 
      for (; i > 0; i--)
        Serial.print((char) (buf[i - 1] < 10 ?
          '0' + buf[i - 1] :
          'A' + buf[i - 1] - 10));
    }
