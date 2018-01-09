package hello.android.sa.dialogue;

import android.app.AlertDialog;
import android.app.Dialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    Button btn;
    FrameLayout f1;
    FrameLayout f2;
    ScrollView s;
    View v,v2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        f1=(FrameLayout) findViewById(R.id.framee);
        s=(ScrollView) findViewById(R.id.sss);
        v=LayoutInflater.from(MainActivity.this).inflate(R.layout.layout,null);
        v2=LayoutInflater.from(MainActivity.this).inflate(R.layout.layout1,null);

    }

    public  void onClicks( View view)
    {
        //Toast.makeText(this, "hello", Toast.LENGTH_LONG).show();
            Button b=(Button)view;
//        AlertDialog.Builder builder=  new AlertDialog.Builder(MainActivity.this);
//        builder.setView(v);
//        builder.setCancelable(true);
//        Dialog dialog= builder.create();
//        dialog.show();
//        f1= (FrameLayout) v.findViewById(R.id.frame1);
//        f2= (FrameLayout) v.findViewById(R.id.frame2);
//        f1.setVisibility(FrameLayout.GONE);
//        f2.setVisibility(FrameLayout.GONE);
        s.removeAllViews();
        switch (view.getId()){

            case R.id.btn1:
                s.addView(v);
                break;
            case R.id.button3:
                s.addView(v2);
                break;
        }







    }

    public  void  ccc(View v)
    {
        Button b=(Button)v;
         if(R.id.bbns==b.getId())
         {
             //Toast.makeText(this, "1", Toast.LENGTH_SHORT).show();
             f1.setVisibility(FrameLayout.GONE);
             f2.setVisibility(FrameLayout.VISIBLE);
         }
        else if(R.id.btns==b.getId())
         {
             Toast.makeText(this, "2", Toast.LENGTH_LONG).show();
             f2.setVisibility(FrameLayout.GONE);
             f1.setVisibility(FrameLayout.VISIBLE);

         }
    }

}


