package aabout.Java.MostlyMathPuzzle;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;

public class Main extends JFrame {

    private JPanel panel;
    private JLabel label;

    public static void main(String[] args) {
        new Main();
    }

    public Main() {

        panel = new JPanel();
        label = new JLabel("Hello, world!");
        panel.add(label);
        this.add(panel);
        this.setSize(200, 200);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        this.setVisible(true);

    }

}
