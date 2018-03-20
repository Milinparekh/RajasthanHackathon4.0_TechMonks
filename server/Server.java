/* Created by Karan Kharecha 
* Team Name: TechMonks
* Date: 19-21 March, 2018
* Description: Program to receive data from the sensor(client) attached on Raspberry Pi.
*/

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.nio.charset.StandardCharsets;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Server {
    public static void main(String[] args) throws IOException{
        ServerSocket serverSocket = new ServerSocket(6776);
        InputStream dataInputStream = serverSocket.accept().getInputStream();
        File file = new File("C:\\Users\\Karan Kharecha\\Desktop\\data.csv"); //Specify the path of the file where data is to be stored permanently
        FileWriter fileWriter = new FileWriter(file, true);
        if (file.length() == 0){
            fileWriter.write("Data,Time,Distance from the Object\n");
        }
        int i;
        String s;
        DateTimeFormatter formatDate = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss"); //Format to print the data on the screen
        DateTimeFormatter dataDate = DateTimeFormatter.ofPattern("dd/MM/yyyy"); //date format to store the date in the csv file
        DateTimeFormatter dataTime = DateTimeFormatter.ofPattern("HH:mm:ss"); //time format to store the time in the csv file
        byte[] buffer = new byte[1024];
        while((i = dataInputStream.read(buffer)) != -1){
            s = new String(buffer, StandardCharsets.UTF_8);
            fileWriter.write(dataDate.format(LocalDateTime.now()) + "," +
                    dataTime.format(LocalDateTime.now()) + "," +
                    s + "\n");
            System.out.println(formatDate.format(LocalDateTime.now()) + ": " + s);
        }
        fileWriter.close();
        dataInputStream.close();
        serverSocket.close();
    }
}