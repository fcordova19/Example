//
//  ViewController.m
//  Example
//
//  Created by desarrollo on 1/14/20.
//  Copyright © 2020 dev. All rights reserved.
//

#import "ViewController.h"
#import "JHFdemo.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
  [super viewDidLoad];
  // Do any additional setup after loading the view.
}


- (IBAction)btnFunction:(UIButton *)sender {
  
  DemoClass dc;
  int n = 0;
  n = dc.FunctionDemo("/Users/desarrollo/Documents/JH/JSON/Demo.json","/Users/desarrollo/Documents/JH/DB/Demo.db3");

    NSString *code = [NSString stringWithFormat:@"%d",n];
    self.txtCode.text = code ;

}
@end


