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

        int pointer = 0;
        int strLength = str.length();
        while (pointer < strLength) {
            if (strLength - pointer < 2) {
                return false;
            }
            switch (str.substring(pointer, pointer + 2)) {
                case "11":
                    pointer += 2;
                    if (strLength - pointer < 2) {
                        return false;
                    }

                    int dataLength = Integer.parseInt(str.substring(pointer, pointer + 2));
                    pointer += 2 + dataLength;
                    break;

                case "12":
                    pointer += 2;
                    if (strLength - pointer < 4) {
                        return false;
                    }

                    int vectorXLength = Integer.parseInt(str.substring(pointer, pointer + 2));
                    int vectorYLength = Integer.parseInt(str.substring(pointer + 2, pointer + 4));
                    pointer += 4 + vectorXLength + vectorYLength;
                    break;

                default:
                    return false;
            }
        }

        return pointer == strLength;

    }

    public static MazeData loadSave(String str) {

        int pointer = 0;
        int strLength = str.length();
        while (pointer < strLength) {
            switch (str.substring(pointer, pointer + 2)) {
                case "11":
                    pointer += 2;
                    int dataLength = Integer.parseInt(str.substring(pointer, pointer + 2));
                    pointer += 2 + dataLength;
                    break;
                case "12":
                    pointer += 2;
                    int vectorXLength = Integer.parseInt(str.substring(pointer, pointer + 2));
                    int vectorYLength = Integer.parseInt(str.substring(pointer + 2, pointer + 4));
                    pointer += 4 + vectorXLength + vectorYLength;
                    break;
            }
        }

        return new MazeData(12345, new Vector2());

    }
    
}
