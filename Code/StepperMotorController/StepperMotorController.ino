//Pin setting
#define step_motor_1 2
#define step_motor_2 3
#define step_motor_3 4
#define step_motor_4 5

#define seg_number_1 6
#define seg_number_2 7
#define seg_number_3 8
#define seg_number_4 9
#define seg_scan_1 10
#define seg_scan_2 11
#define seg_scan_3 12

#define LED 13

#define btn_1 A0
#define btn_2 A1
#define btn_3 A2
#define btn_4 A3
#define btn_5 A4

short Step_Motor_Direction (short);

void setup() {
    pinMode(step_motor_1, OUTPUT);
    pinMode(step_motor_2, OUTPUT);
    pinMode(step_motor_3, OUTPUT);
    pinMode(step_motor_4, OUTPUT);
    pinMode(seg_number_1, OUTPUT);
    pinMode(seg_number_2, OUTPUT);
    pinMode(seg_number_3, OUTPUT);
    pinMode(seg_number_4, OUTPUT);
    pinMode(seg_scan_1,   OUTPUT);
    pinMode(seg_scan_2,   OUTPUT);
    pinMode(seg_scan_3,   OUTPUT);
    pinMode(LED,          OUTPUT);

    pinMode(btn_1, INPUT);
    pinMode(btn_2, INPUT);
    pinMode(btn_3, INPUT);
    pinMode(btn_4, INPUT);
    pinMode(btn_5, INPUT);
}

short count_step = 0, module_step_count = 0;

short delay_time = 0, count_delay_time = 0, step_motor_200 = 0, show_seg_number = 0;
bool change_model = false, before_change_model = false, working = false, start_working = false;

void loop() {
    while (1) {
        if(working == false) {
            count_delay_time++;
            if (count_delay_time == 1000) {
                count_delay_time = 0;
                working = true;
            }
        }



        delay_time++;
        if (delay_time == 5) {
            delay_time = 0;
            Select_Module();
        }

        delay(1);
    }
    
}

bool Read_BTN_3 () {
    bool 

        working = digitalRead(btn_3);
}

void Select_Module (void) {
    bool sel_m;
    sel_m = digitalRead(btn_1);
    
    if (sel_m == true) {
        Module_1();
    }
    else {
        Module_2();
    }
}

void Module_1 (void) {
    if (working == true) {
        count_step++;
        if (count_step > 4) {
            count_step = 1;
        }
    }
    else {
        count_step = 0;
    }
    Step_Motor_Running(count_step);
}

void Module_2 (void) {
    if (working == true) {
        count_step++;
        if (count_step > 4) {
            count_step = 1;
        }

        module_step_count++;
        if (module_step_count == 200) {
            module_step_count = 0;
            working = false;
        }
    }
    else {
        count_step = 0;
    }
    Step_Motor_Running(count_step);
}

//控制馬達轉動
void Step_Motor_Running (short step) {
    switch (Step_Motor_Direction(step)) {
        case 1:
            digitalWrite(step_motor_1, HIGH);
            digitalWrite(step_motor_2,  LOW);
            digitalWrite(step_motor_3,  LOW);
            digitalWrite(step_motor_4,  LOW);
            break;
        case 2:
            digitalWrite(step_motor_1,  LOW);
            digitalWrite(step_motor_2, HIGH);
            digitalWrite(step_motor_3,  LOW);
            digitalWrite(step_motor_4,  LOW);
            break;
        case 3:
            digitalWrite(step_motor_1,  LOW);
            digitalWrite(step_motor_2,  LOW);
            digitalWrite(step_motor_3, HIGH);
            digitalWrite(step_motor_4,  LOW);
            break;
        case 4:
            digitalWrite(step_motor_1,  LOW);
            digitalWrite(step_motor_2,  LOW);
            digitalWrite(step_motor_3,  LOW);
            digitalWrite(step_motor_4, HIGH);
            break;
        default:
            digitalWrite(step_motor_1,  LOW);
            digitalWrite(step_motor_2,  LOW);
            digitalWrite(step_motor_3,  LOW);
            digitalWrite(step_motor_4,  LOW);
            break;
    }
}

//轉換方向
short Step_Motor_Direction (short step) {
    bool Clockwise;
    Clockwise = digitalRead(btn_2);
    
    if (step == 0) { //表示停止轉動
        return 0;
    }
    else {
        // True = 順時針, False = 逆時針
        if (Clockwise == true) {
            return step; //順時針
        }
        else {
            return (5 - step); //逆時針
        }
    }
}
