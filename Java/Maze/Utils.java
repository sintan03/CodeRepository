package aabout.Java.Maze;

public class Utils {
    
    public static void out(Object... values) {
        for (Object value : values) {
            System.out.println(value);
        }
    }
    
    public static int randomInt(int min, int max) {
        return (int) (Math.random() * (max - min + 1) - min);
    }
    
    public static int randomInt(int max) { return randomInt(0, max); }
    public static int randomInt() { return randomInt(0, 1); }
    
}