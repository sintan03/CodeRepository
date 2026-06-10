package aabout.Java.Maze;

import java.util.Scanner;

public class Main {
    
    public static void main(String[] args) {
        
        Scanner scan = new Scanner(System.in);
        MazeData mazeData;
        Utils.out("New Game?(y/n): ");
        String str = scan.next();
        
        if (str.equals("y")) {
            Utils.out(Utils.randomInt(100));
        } else {
            do {
                Utils.out("Save Data?(\"q\" is quit): ");
                str = scan.next();
            } while (!(str.equals("q") || MazeUtils.testSave(str)));
            Utils.out(MazeUtils.testSave(str));
        }
        
    }
    
}