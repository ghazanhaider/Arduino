
    #include <SPI.h>
    #include <SdFat.h>
 
    SdFat sd;
    SdFile file;
    
 
    const int chipSelect = 5;
 
    void setup()
    {
   
      sd.begin(chipSelect, SD_SCK_MHZ(50));
      file.open("HELLO.txt", O_WRONLY | O_CREAT | O_EXCL);
      file.print("Hello");
      file.println("World");
      file.close();
 }
 
 
    void loop(void) {
 
    }
------------------------------
