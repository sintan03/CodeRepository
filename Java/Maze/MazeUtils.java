package aabout.Java.Maze;

import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MazeUtils {
    
    public static boolean testSave(String str) {
        
        Pattern p = Pattern.compile("\\d");
        Matcher m = p.matcher(str);
        if (!m.find()) {
            return false;
        }
        return true;
        
    }
    
}
