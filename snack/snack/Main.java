package snack;


import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class Main extends JPanel{

    public static final int ROWS = 38;//行数
    public static final int COLS = 40;//列数
    public static final int CELL_SIZE = 20;//格子大小10个像素

    public static Image background;

    public static Image foodImage;

    public static Image cellImage;

    private Move worm;

    private Node food;

    public Main() {
        background = Toolkit.getDefaultToolkit().
                createImage("D:\\idea_program\\java_learning\\src\\main\\java\\snack\\bg.jpeg");
        foodImage = Toolkit.getDefaultToolkit().
                createImage("D:\\idea_program\\java_learning\\src\\main\\java\\snack\\food.jpeg");
        cellImage = Toolkit.getDefaultToolkit().
                createImage("D:\\idea_program\\java_learning\\src\\main\\java\\snack\\node.jpeg");
        worm = new Move();
        food = createFood();
    }

    private Node createFood() {
        int x;
        int y;
        Random r = new Random();
        do {
            x = r.nextInt(COLS-1);
            y = r.nextInt(ROWS-1);
        }while (worm.contains(x,y));
        return new Node(x,y);
    }



    @Override
    public String toString() {
        return "Main{" +
                "worm=" + worm +
                ", food=" + food +
                '}';
    }

    /** 重写绘图方法 */
    public void paint(Graphics g) {
        // 填充背景色
        g.drawImage(background, 0, 0, null);
//        System.out.println("背景色成功了吗？"+g.drawImage(background, 0, 0,null));
        // 绘制食物
        g.translate(0, 0);
        g.drawImage(foodImage,
                CELL_SIZE * food.getX(), CELL_SIZE * food.getY(), 20,20,null);
        // 绘制蛇
        Node[] cells = worm.getCells();
        for (int i = 0; i < cells.length; i++) {
            Node node = cells[i];
            g.drawImage(cellImage,
                    CELL_SIZE * node.getX(), CELL_SIZE * node.getY(), 20,20,null);

        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("贪吃蛇");
//        JPanel jPanel = new JPanel();
        Main pane = new Main();
        frame.add(pane);
        frame.setSize(800,760);//设置窗口大小
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pane.action();

    }

    private void action() {
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                if(worm.hit()){//撞到了
                    worm = new Move();
                    food = createFood();
                }else {
                    boolean eat = worm.creep(food);
                    if(eat){
                        food = createFood();//吃到食物了
                    }
                }
                repaint();
            }
        },0,100);
        //this 就是当前舞台面板
        this.requestFocus();
        this.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                //key 代表哪个键被按下
                int key = e.getKeyCode();
                switch (key){
                    case KeyEvent.VK_UP:
                        creepTo(Move.UP);
                        break;
                    case KeyEvent.VK_DOWN:
                        creepTo(Move.DOWN);
                        break;
                    case KeyEvent.VK_LEFT:
                        creepTo(Move.LEFT);
                        break;
                    case KeyEvent.VK_RIGHT:
                        creepTo(Move.RIGHT);
                        break;
                }
            }
        });
    }


    /**
     * 爬行控制方法，在按键按下时候调用
     * @param direction 按键方向
     */
    private void creepTo(int direction) {
        if (worm.hit(direction)){//撞到了
            worm = new Move();
            food = createFood();
        }else{
            boolean eat = worm.creep(direction, food);
            if (eat){
                food = createFood();//按键吃到了
            }
        }
        repaint();
    }


}
