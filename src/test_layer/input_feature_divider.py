import sys
import cv2
import argparse
import numpy as np

parser = argparse.ArgumentParser(description='input feature map divider')
# python input_feature_divider.py --input_enable 1 --input_feature_map 'cat_jpg' --input_width 8 --input_height 8 --input_channel 3 --kernel_width 3 --kernel_height 3 --kernel_channel 3 --stride 1 --padding 0
parser.add_argument('--input_enable', default=0, type=int, help='input feature map divider enable')
parser.add_argument('--weight_enable', default=0, type=int, help='weight matrix divider enable')
parser.add_argument('--image_enable', default=0, type=int, help='input is an image or not')
parser.add_argument('--input_feature_map', default='default.jpg', type=str, help='input feature map')
parser.add_argument('--weight_matrix', default='default.txt', type=str, help='weight matrix')
parser.add_argument('--input_width', default=224, type=int, help='input feature width')
parser.add_argument('--input_height', default=224, type=int, help='input feature height')
parser.add_argument('--input_channel', default=3, type=int, help='input feature channel')
parser.add_argument('--kernel_width', default=3, type=int, help='kernel width')
parser.add_argument('--kernel_height', default=3, type=int, help='kernel height')
parser.add_argument('--kernel_channel', default=3, type=int, help='kernel channel')
parser.add_argument('--kernel_number', default=64, type=int, help='kernel number')
parser.add_argument('--stride', default=1, type=int, help='stride')
parser.add_argument('--padding', default=0, type=int, help='padding')
parser.add_argument('--tile_width', default=64, type=int, help='tile width')
parser.add_argument('--tile_height', default=64, type=int, help='tile height')

def main():
     global args
     args = parser.parse_args()

     if args.input_enable:
          if args.image_enable:
               matx = cv2.imread(args.input_feature_map)
               matx_resize = cv2.resize(matx, (args.input_width, args.input_height), interpolation=cv2.INTER_NEAREST)
               matx_padding = cv2.copyMakeBorder(matx_resize, args.padding, args.padding, args.padding, args.padding, cv2.BORDER_CONSTANT, 0)
          else:
               read_file = open(args.input_feature_map, mode = "r")
               line = read_file.read()
               list = line.split()
               matx = np.zeros([args.input_width, args.input_height, args.input_channel])
               index = 0
               for i in range(args.input_height):
                    for j in range(args.input_width):
                         for k in range(args.input_channel):
                              matx[j][i][k] = list[index]
                              index = index + 1
               matx_padding = cv2.copyMakeBorder(matx, args.padding, args.padding, args.padding, args.padding, cv2.BORDER_CONSTANT, 0)

          index_w = 0
          index_h = 0
          index_c = 0
          file_number1 = 1
          while index_h < matx_padding.shape[0] - args.kernel_height + 1:
               file_number2 = 1
               counter = 0
               for i in range(args.kernel_channel):
                    for j in range(args.kernel_height):
                         for k in range(args.kernel_width):
                              if counter == args.tile_height:
                                   file_number2 = file_number2 + 1
                                   counter = 0
                              new_file = open("./input/input" + str(file_number2) + "_" + str(file_number1) + ".txt", mode = "a")
                              # new_file.write("matx[%d][%d][%d] = %d\n" %(index_h + j, index_w + k, index_c + i, matx_padding[index_h + j][index_w + k][index_c + i]))
                              new_file.write("%d\n" %matx_padding[index_h + j][index_w + k][index_c + i])
                              new_file.close
                              counter = counter + 1
               index_w = index_w + args.stride
               file_number1 = file_number1 + 1
               if index_w >= matx_padding.shape[1] - args.kernel_width + 1:
                    index_w = 0
                    index_h = index_h + args.stride

     if args.weight_enable:
          read_file = open(args.weight_matrix, mode = "r")
          line = read_file.read()
          list = line.split()
          number = args.kernel_width * args.kernel_height * args.kernel_channel
          index = 0
          file_number2 = 1
          counter1 = 0
          for i in range(args.kernel_number):
               counter = 0
               file_number1 = 1
               counter1 = counter1 + 1
               for j in range(number):
                    if counter == args.tile_height:
                         file_number1 = file_number1 + 1
                         counter = 0
                    new_file = open("./weight/weight" + str(file_number2) + "_" + str(file_number1) + ".txt", mode = "a")
                    new_file.write(list[index])
                    new_file.write("\n")
                    new_file.close
                    index = index + 1
                    counter = counter + 1
               # if counter != args.tile_height:
               #      for j in range(counter, args.tile_height):
               #           new_file = open("./weight/weight" + str(file_number2) + "_" + str(file_number1) + ".txt", mode = "a")
               #           new_file.write("0\n")
               #           new_file.close
               if counter1 == args.tile_width / 8:
                    file_number2 = file_number2 + 1
                    counter1 = 0
                    
if __name__ == '__main__':
    main()
