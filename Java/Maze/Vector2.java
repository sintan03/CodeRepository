package aabout.Java.Maze;

public class Vector2 {
    
    private double x = 0;
    private double y = 0;
    
    public Vector2(double x, double y) {
        this.x = x;
        this.y = y;
    }
    
    public Vector2(double x) { new Vector2(x, 0); }
    public Vector2() { new Vector2(0, 0); }
    
    public String get() {
        return String.valueOf(x) + "," + String.valueOf(y);
    }
    
}