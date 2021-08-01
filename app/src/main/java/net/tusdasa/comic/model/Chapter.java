package net.tusdasa.comic.model;

public class Chapter {

    private Long chapter_id;

    private Integer order_id;

    private String title;

    private Long comic_id;

    private Integer total;

    public Chapter() {
    }

    public Long getChapter_id() {
        return chapter_id;
    }

    public void setChapter_id(Long chapter_id) {
        this.chapter_id = chapter_id;
    }

    public Integer getOrder_id() {
        return order_id;
    }

    public void setOrder_id(Integer order_id) {
        this.order_id = order_id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public Long getComic_id() {
        return comic_id;
    }

    public void setComic_id(Long comic_id) {
        this.comic_id = comic_id;
    }

    public Integer getTotal() {
        return total;
    }

    public void setTotal(Integer total) {
        this.total = total;
    }

    @Override
    public String toString() {
        return "Chapter{" +
                "chapter_id=" + chapter_id +
                ", order_id=" + order_id +
                ", title='" + title + '\'' +
                ", comic_id=" + comic_id +
                ", total=" + total +
                '}';
    }
}
