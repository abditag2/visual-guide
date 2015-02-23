function [outputImg] = edgeDetection(name, type, thresh, direction)

%  Jeffrey Huang
%  
%  Definition: edgeDetection(file_path, type, thresh, additional)
%  Inputs: file_path: Path to the file to read
%          type: 0 - 4, types of filters
%          thresh (optional): Threshold of the filter
%          direction (optional): Direction of the filter
%  Outpus: A filtered image
%  Side Effects: None

I = imread(name);
I = rgb2gray(I);

switch type
    case 0
        disp('Using canny method');
        if (nargin < 3) || isempty(thresh)
            outputImg = edge(I, 'canny');
        else if (nargin < 4) || isempty(direction)
                outputImg = edge(I, 'canny', thresh);
            else 
                outputImg = edge(I, 'canny', thresh, direction);
            end
        end
    case 1
        disp('Using sobel method');
        if (nargin < 3) || isempty(thresh)
            outputImg = edge(I, 'sobel');
        else if (nargin < 4) || isempty(direction)
                outputImg = edge(I, 'sobel', thresh);
            else 
                outputImg = edge(I, 'sobel', thresh, direction);
            end
        end
    case 2
        disp('Using prewitt method');
        if (nargin < 3) || isempty(thresh)
            outputImg = edge(I, 'prewitt');
        else if (nargin < 4) || isempty(direction)
                outputImg = edge(I, 'prewitt', thresh);
            else 
                outputImg = edge(I, 'prewitt', thresh, direction);
            end
        end
    case 3
        disp('Using roberts method');
        if (nargin < 3) || isempty(thresh)
            outputImg = edge(I, 'roberts');
        else 
            outputImg = edge(I, 'roberts', thresh);
        end
    case 4
        disp('Using laplacian method');
        if (nargin < 3) || isempty(thresh)
            outputImg = edge(I, 'log');
        else if (nargin < 4) || isempty(direction)
                outputImg = edge(I, 'log', thresh);
            else 
                outputImg = edge(I, 'log', thresh, direction);
            end
        end
    otherwise
        disp('Edge detection uses');
        disp('-----------------------------');
        disp('edgeDetection(filename, type, threshold, direction/sigma/filter)');
        disp('0) canny');
        disp('1) sobel');
        disp('2) prewitt');
        disp('3) roberts');
        disp('4) laplacian');
end
        