package snack;

import java.util.Arrays;

public class Move {
    public static final int DEFAULT_LENGTH = 5;//贪吃蛇初始长度
    private Node[] cells;

    public static final int UP = 1;
    public static final int DOWN = -1;
    public static final int LEFT = 2;
    public static final int RIGHT = -2;

    private int currentDirection;//蛇当前运行方向

    public Move() {
        cells = new Node[DEFAULT_LENGTH];
        for (int i = 0; i < cells.length; i++){
            cells[i] = new Node(i,0);
        }
        currentDirection = DOWN;//当前运行方向向下。
        System.out.println(currentDirection);
    }

    /**
     * 判断食物是否在蛇身体里
     * @param x 随机生成的食物x坐标
     * @param y 随机生成的食物y坐标
     * @return
     */
    public boolean contains(int x, int y){
        for (int i = 0; i < cells.length; i++){
            Node node = cells[i];
            if (node.getX() == x && node.getY() == y){
                return true;
            }
        }
        return false;
    }

    public boolean hit(){ return hit(currentDirection);}

    public boolean hit(int direction){
//        System.out.println("currentDirection:"+currentDirection+"direction:"+direction);
        if (currentDirection + direction == 0){//反向不处理碰撞？？？
//            System.out.println("反向不处理碰撞,currentDirection:"+currentDirection+"direction:"+direction);
            return false;
        }
        Node head = createHead(direction);
//        System.out.println("head.getX():"+head.getX()+"head.getY():"+head.getY());
//        System.out.println("Main.COLS:"+Main.COLS+"Main.ROWS:"+Main.ROWS);
        if (head.getX() < 0 || head.getX() >= Main.COLS || head.getY() < 0 || head.getY() >= Main.ROWS){
            System.out.println("撞墙了！");
            return true;
        }
        for (int i = 0; i < cells.length-1; i++){
            Node node = cells[i];
            if (node.getX() == head.getX() && node.getY() == head.getY()){
                System.out.println("撞到自己身体了！");
                return true;
            }
        }
        return false;
    }

    public boolean creep(Node food){ return creep(currentDirection, food);}

    public boolean creep(int direction, Node food){
        if (currentDirection + direction == 0){
            return false; // 反向了,不进行任何动作
        }
        currentDirection = direction;//赋予蛇运行新方向
        Node head = createHead(direction);//蛇头位置
        boolean eat = head.getX() == food.getX() && head.getY() == food.getY();//判断是否吃到食物（蛇头位置是否和食物位置相同）
//        System.out.println("吃到了吗？"+eat);
        if(eat){
            cells = Arrays.copyOf(cells, cells.length + 1);//蛇长度加1
        }
        //重新绘制蛇身数组,数组往后挪1位，cells[0]挪到cells[1]
        for(int i = cells.length-1; i>=1;i--){
            cells[i] = cells[i-1];
        }
        //cells[0]蛇头位置还是原来的head位置
        cells[0] = head;
        return eat;

    }

    private Node createHead(int direction) {
        int x = cells[0].getX();
        int y = cells[0].getY();
        switch (direction){
            case DOWN:
                y++;
                break;
            case UP:
                y--;
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
        }
        return new Node(x,y);
    }

    public Node[] getCells() { return Arrays.copyOf(cells, cells.length);}

    @Override
    public String toString() {
        System.out.println(Arrays.toString(cells));
        return Arrays.toString(cells);
    }
}
